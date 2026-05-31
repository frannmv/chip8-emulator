#ifndef CHIP8_H
#define CHIP8_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define MEMORY_SIZE 4096
#define SCALE 10
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32


void initialize(void);
void load_game(char* path);
void clear_screen();
void finish();
uint8_t get_key();
void update_timers();

#endif /* CHIP8_H */