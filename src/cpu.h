#ifndef CPU_H
#define CPU_H

#include "chip8.h"

SDL_Event event;
uint64_t last_timer_update;

void cycle();
uint8_t get_key();
void update_timers();
void clear_screen();

#endif /* CPU_H */