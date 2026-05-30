#include "utils.h"

int main(int argc, char **argv) {

    if(argc < 2) {
        fprintf(stderr, "usage: %s path/to/file.ch8\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* path = argv[1];
    pc = 512;

    load_game(path);

    return 0;
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

        printf("byte read: 0x%02X\n", c);
        memory[aux] = c;
        aux++;
        cant_bytes++;
    }

    printf("TOTAL BYTES: %d\n", cant_bytes);
    fclose(file);
}