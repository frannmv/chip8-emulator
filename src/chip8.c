#include "chip8.h"

uint8_t memory[MEMORY_SIZE];
uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
uint8_t keypad[16];  
uint8_t V[16];
uint16_t stack[16];
uint8_t sp;
uint16_t pc;
uint16_t I;
uint8_t delay_timer;
uint8_t sound_timer;
uint8_t font[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0  
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
SDL_Window *window;
SDL_Renderer *renderer;

void initialize() {

    pc = 0x0200;
    I = 0;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;

    for(uint8_t i = 0; i < 16; i++) {
        keypad[i] = 0;
    }

    for(uint8_t i = 0; i < 80; i++) {
        memory[i] = font[i];
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("CHIP-8 EMULATOR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE, 0);

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
    
    FILE *file = fopen(path,"rb");
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

        memory[aux++] = c;
        cant_bytes++;
    }

    fclose(file);
}

void finish() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
