#include "utils.h"

int main(int argc, char **argv) {

    if(argc < 2) {
        fprintf(stderr, "usage: %s path/to/file.ch8\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* path = argv[1];

    initialize();
    load_game(path);

    while(1) {

        SDL_Event event;

        while(SDL_PollEvent(&event)) {

        };

        uint8_t inst_1 = memory[pc++];
        uint8_t inst_2 = memory[pc++];

        uint16_t opcode = (inst_1 << 8) | inst_2;
        uint8_t to_exec;

        switch(opcode & 0xF000) {
            case 0x0000: // TODO
                to_exec = memory[opcode & 0xFFF]; // Calls machine code routine at address NNN. (Maybe stop the execution of the ROM)
                break;
            case 0x1000: // TODO
                to_exec = memory[opcode & 0xFFF]; // Jumps to address NNN
                break;
            case 0x2000: // TODO
                to_exec = memory[opcode & 0xFFF]; // Calls subroutine at NNN
                break;
            case 0x3000:
                if(V[(opcode & 0x0F00) >> 8] == opcode & 0x00FF) pc++;
                break;
            case 0x4000:
                if(V[(opcode & 0x0F00) >> 8] != opcode & 0x00FF) pc++;
                break;
            case 0x5000:
                if(V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) pc++;
                break;
            case 0x6000:
                V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
                break;
            case 0x7000:
                V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
                break;
            case 0x8000:
                switch(opcode & 0x000F) {
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
                    case 0x0004:
                        V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
                        break;
                    case 0x0005:
                        V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
                        break;
                    case 0x0006:
                        V[(opcode & 0x0F00) >> 8] >>= 1;
                        break;
                    case 0x0007:
                        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
                        break;
                    case 0x000E:
                        V[(opcode & 0x0F00) >> 8] <<= 1;
                        break;
                }
                break;
            case 0x9000:
                if(V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) pc++;
                break;
            case 0xA000:
                I = opcode & 0xFFF; // Set I to the address NNN
                break;
            case 0xB000: // TODO
                to_exec = memory[opcode & 0xFFF]; // Jumps to the address NNN plus V0
                break;
            case 0xC000:
                V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
                break;
            case 0xD000:
                uint8_t x = V[(opcode & 0x0F00) >> 8];
                uint8_t y = V[(opcode & 0x00F0) >> 4];
                uint8_t height = opcode & 0x000F;
                
                V[0xF] = 0;
                for(int row = 0; row < height; row++) {
                    
                    uint8_t sprite = memory[I + row];
                    
                    for(int col = 0; col < 8; col++) {
                        if(sprite & (0x80 >> col)) {
                            if(screen[y + row][x + col]) {
                                V[0xF] = 1;
                            }
                            screen[y + row][x + col] ^= 1;
                        }
                    }
                }
                break;
            case 0xE000:
                break;
            case 0xF000:
                break;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for(int row = 0; row < SCREEN_HEIGHT; row++) {
            for(int col = 0; col < SCREEN_WIDTH; col++) {
                if(screen[row][col]) {
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

    finish();
    return 0;
}

void finish() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void initialize() {

    pc = 0x0200;
    I = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if(window == NULL) {
        fprintf(stderr, "Window could not be created!\n"
                "SDL_ERROR: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    };

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(renderer == NULL) {
        fprintf(stderr, "Render could not be created!\n"
                "SDL_ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }; 
}

void load_game(char* path) {
    
    FILE *file = fopen(path,"r");
    if(file == NULL) {
        fprintf(stderr, "Could not open %s\n", path);
        exit(EXIT_FAILURE);
    }

    uint16_t aux = pc;
    int c;
    int cant_bytes = 0;
    while((c = getc(file)) != EOF) {

        if(aux >= MEMORY_SIZE) {
            fprintf(stderr, "ROM too large for memory\n");
            exit(EXIT_FAILURE);
        }

  //      printf("byte read: 0x%02X\n", c);
        memory[aux++] = c;
        cant_bytes++;
    }

    printf("TOTAL BYTES: %d\n", cant_bytes);
    fclose(file);
}