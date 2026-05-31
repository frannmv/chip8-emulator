CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -Isrc $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

TARGET  = chip8
SRCS    = src/main.c src/chip8.c src/cpu.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/main.o:  src/main.c src/chip8.h
src/chip8.o: src/chip8.c src/chip8.h
src/cpu.o:   src/cpu.c src/cpu.h src/chip8.h

clean:
	rm -f $(OBJS) $(TARGET)