#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define MEMORY_SIZE 4096
#define SCALE 10
#define SCREEN_WIDTH 64 * SCALE
#define SCREEN_HEIGHT 32 * SCALE

char memory[MEMORY_SIZE];

uint8_t screen[SCREEN_WIDTH][SCREEN_HEIGHT];
uint8_t V[16];
uint16_t pc;
uint16_t I;

SDL_Window *window;
SDL_Renderer *renderer;

void initialize(void);
void load_game(char* path);
void finish();

#endif /* UTILS_H */