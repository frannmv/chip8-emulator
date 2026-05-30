#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEMORY_SIZE 4096

char memory[MEMORY_SIZE];

uint8_t V[16];
uint16_t pc;

void load_game(char* path);

#endif /* UTILS_H */