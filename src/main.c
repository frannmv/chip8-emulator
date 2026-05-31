#include "chip8.h"

int main(int argc, char **argv) {

    if(argc < 2) {
        fprintf(stderr, "usage: %s roms/<rom_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* path = argv[1];

    initialize();
    load_game(path);
    cycle();
    finish();

    return 0;
}