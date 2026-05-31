#ifndef CHIP8_H
#define CHIP8_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define MEMORY_SIZE 4096
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCALE 10

extern uint8_t memory[MEMORY_SIZE];
extern uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
extern uint8_t keypad[16];  
extern uint8_t V[16];
extern uint16_t stack[16];
extern uint8_t sp;
extern uint16_t pc;
extern uint16_t I;
extern uint8_t delay_timer;
extern uint8_t sound_timer;
extern uint8_t font[80];


extern SDL_Window *window;
extern SDL_Renderer *renderer;

void initialize(void);
void load_game(char* path);
void finish();

#endif /* CHIP8_H */


