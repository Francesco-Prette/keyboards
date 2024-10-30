CC = gcc
CFLAGS = -Wall -std=c11 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LDFLAGS)

clean:
	rm -f main
