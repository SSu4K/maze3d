all: main

main: main.o game.o renderer.o level.o raycaster.o
	gcc -fsanitize=undefined -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<


level.o: level.c level.h

raycaster.o: raycaster.c raycaster.h level.h

renderer.o: renderer.c renderer.h

game.o: game.c game.h

main.o: main.c game.h

clean:
	-rm level.o raycaster.o renderer.o game.o main.o main