#include "cpu.h"

void cycle() {
    last_timer_update = SDL_GetTicks64();
    int quit = 0;
    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        keypad[0] = 0;
                        break;
                    case SDLK_2:
                        keypad[1] = 0;
                        break;
                    case SDLK_3:
                        keypad[2] = 0;
                        break;
                    case SDLK_4:
                        keypad[3] = 0;
                        break;
                    case SDLK_q:
                        keypad[4] = 0;
                        break;
                    case SDLK_w:
                        keypad[5] = 0;
                        break;
                    case SDLK_e:
                        keypad[6] = 0;
                        break;
                    case SDLK_r:
                        keypad[7] = 0;
                        break;
                    case SDLK_a:
                        keypad[8] = 0;
                        break;
                    case SDLK_s:
                        keypad[9] = 0;
                        break;
                    case SDLK_d:
                        keypad[10] = 0;
                        break;
                    case SDLK_f:
                        keypad[11] = 0;
                        break;
                    case SDLK_z:
                        keypad[12] = 0;
                        break;
                    case SDLK_x:
                        keypad[13] = 0;
                        break;
                    case SDLK_c:
                        keypad[14] = 0;
                        break;
                    case SDLK_v:
                        keypad[15] = 0;
                        break;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        keypad[0] = 1;
                        break;
                    case SDLK_2:
                        keypad[1] = 1;
                        break;
                    case SDLK_3:
                        keypad[2] = 1;
                        break;
                    case SDLK_4:
                        keypad[3] = 1;
                        break;
                    case SDLK_q:
                        keypad[4] = 1;
                        break;
                    case SDLK_w:
                        keypad[5] = 1;
                        break;
                    case SDLK_e:
                        keypad[6] = 1;
                        break;
                    case SDLK_r:
                        keypad[7] = 1;
                        break;
                    case SDLK_a:
                        keypad[8] = 1;
                        break;
                    case SDLK_s:
                        keypad[9] = 1;
                        break;
                    case SDLK_d:
                        keypad[10] = 1;
                        break;
                    case SDLK_f:
                        keypad[11] = 1;
                        break;
                    case SDLK_z:
                        keypad[12] = 1;
                        break;
                    case SDLK_x:
                        keypad[13] = 1;
                        break;
                    case SDLK_c:
                        keypad[14] = 1;
                        break;
                    case SDLK_v:
                        keypad[15] = 1;
                        break;
                }
                break;
            }
        }

        uint8_t inst_1 = memory[pc++];
        uint8_t inst_2 = memory[pc++];

        uint16_t opcode = (inst_1 << 8) | inst_2;

        switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x00FF) {
                case 0x00E0:
                    clear_screen();
                    break;
                case 0x00EE:
                    pc = stack[--sp];
                    break;
            }
            break;
        case 0x1000:
            pc = opcode & 0x0FFF;
            break;
        case 0x2000:
            stack[sp++] = pc;
            pc = opcode & 0x0FFF;
            break;
        case 0x3000:
            if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
                pc += 2;
            break;
        case 0x4000:
            if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
                pc += 2;
            break;
        case 0x5000:
            if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
                pc += 2;
            break;
        case 0x6000:
            V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
            break;
        case 0x7000:
            V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
            break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0001:
                    V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0002:
                    V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0003:
                    V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0004: {
                    uint16_t res = V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4];
                    if (res > 255) {
                        V[0xF] = 1;
                    } else {
                        V[0xF] = 0;
                    }
                    V[(opcode & 0x0F00) >> 8] = (res & 0x00FF);
                    break;
                }
                case 0x0005:
                    if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
                        V[0xF] = 1;
                    } else {
                        V[0xF] = 0;
                    }
                    V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0006:
                    V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
                    V[(opcode & 0x0F00) >> 8] >>= 1;
                    break;
                case 0x0007:
                    if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
                        V[0xF] = 0;
                    } else {
                        V[0xF] = 1;
                    }
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x000E:
                    V[0xF] = (V[(opcode & 0x0F00) >> 8] & 0x80) >> 7;
                    V[(opcode & 0x0F00) >> 8] <<= 1;
                    break;
            }
            break;
        case 0x9000:
            if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
                pc += 2;
            break;
        case 0xA000:
            I = opcode & 0xFFF; // Set I to the address NNN
            break;
        case 0xB000:
            pc = V[0] + (opcode & 0x0FFF);
            break;
        case 0xC000:
            V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
            break;
        case 0xD000: {
            uint8_t x = V[(opcode & 0x0F00) >> 8];
            uint8_t y = V[(opcode & 0x00F0) >> 4];
            uint8_t height = opcode & 0x000F;

            V[0xF] = 0;
            for (int row = 0; row < height; row++) {

                uint8_t sprite = memory[I + row];

                for (int col = 0; col < 8; col++) {
                    if (sprite & (0x80 >> col)) {
                        if (screen[y + row][x + col]) {
                            V[0xF] = 1;
                        }
                        screen[y + row][x + col] ^= 1;
                    }
                }
            }
            break;
        }
        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E:
                    if (keypad[V[(opcode & 0x0F00) >> 8]])
                        pc += 2;
                    break;
                case 0x00A1:
                    if (!keypad[V[(opcode & 0x0F00) >> 8]])
                        pc += 2;
                    break;
            }
            break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    V[(opcode & 0x0F00) >> 8] = delay_timer;
                    break;
                case 0x000A:
                    V[(opcode & 0x0F00) >> 8] = get_key();
                    break;
                case 0x0015:
                    delay_timer = V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x0018:
                    sound_timer = V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x001E:
                    I += V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x0029:
                    I = V[(opcode & 0x0F00) >> 8] * 5;
                    break;
                case 0x0033:
                    memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
                    memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
                    memory[I + 2] = (V[(opcode & 0x0F00) >> 8]) % 10;
                    break;
                case 0x0055:
                    for (uint8_t i = 0; i <= V[(opcode & 0x0F00) >> 8]; i++) {
                        memory[I + i] = V[i];
                    }
                    break;
                case 0x0065:
                    for (uint8_t i = 0; i <= V[(opcode & 0x0F00) >> 8]; i++) {
                        V[i] = memory[I + i];
                    }
                    break;
            }
            break;
        }

        update_timers();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for (int row = 0; row < SCREEN_HEIGHT; row++) {
            for (int col = 0; col < SCREEN_WIDTH; col++) {
                if (screen[row][col]) {
                    SDL_Rect rect;
                    rect.x = col * SCALE;
                    rect.y = row * SCALE;
                    rect.h = SCALE;
                    rect.w = SCALE;
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void update_timers() {

    uint64_t current_ticks = SDL_GetTicks64();
    if (current_ticks - last_timer_update >= 16) {
        if (delay_timer > 0)
            delay_timer--;
        if (sound_timer > 0)
            sound_timer--;
        last_timer_update = current_ticks;
    }
}

uint8_t get_key() {

    while (1) {

        if (SDL_WaitEvent(&event) == 0) {
            fprintf(stderr, "Error while waiting for events!\n"
                            "SDL_ERROR: %s\n",
                    SDL_GetError());
            finish();
            exit(EXIT_FAILURE);
        }

        if (event.type != SDL_KEYDOWN)
            continue;

        switch (event.key.keysym.sym) {
        case SDLK_1:
            return 0;
        case SDLK_2:
            return 1;
        case SDLK_3:
            return 2;
        case SDLK_4:
            return 3;
        case SDLK_q:
            return 4;
        case SDLK_w:
            return 5;
        case SDLK_e:
            return 6;
        case SDLK_r:
            return 7;
        case SDLK_a:
            return 8;
        case SDLK_s:
            return 9;
        case SDLK_d:
            return 10;
        case SDLK_f:
            return 11;
        case SDLK_z:
            return 12;
        case SDLK_x:
            return 13;
        case SDLK_c:
            return 14;
        case SDLK_v:
            return 15;
        }
    }
}

void clear_screen() {
    for (int row = 0; row < SCREEN_HEIGHT; row++) {
        for (int col = 0; col < SCREEN_WIDTH; col++) {
            screen[row][col] = 0;
        }
    }
}
