print_h  = src/includes/print.h
screen_h = src/includes/screen.h $(print_h)
snake_h  = src/includes/snake.h $(print_h)
board_h  = src/includes/board.h $(snake_h)
game_h   = src/includes/game.h $(board_h) $(print_h) $(screen_h) $(snake_h) 

C = gcc -Wall -Wextra -Werror -O2 -std=c99 -pedantic -g3
# O = $C src/$1.c && mv $2.o lib/

targets = lib/board.o lib/screen.o lib/snake.o lib/game.o
default: src/main.c $(targets) $(print_h)
	$C -o main src/main.c $(targets)

lib/board.o: src/board.c $(board_h)
	$C -c src/board.c
	mv board.o lib/

lib/screen.o: src/screen.c $(screen_h)
	$C -c src/screen.c
	mv screen.o lib/

lib/snake.o: src/snake.c $(snake_h)
	$C -c src/snake.c
	mv snake.o lib/

lib/game.o: src/game.c $(game_h)
	$C -c src/game.c
	mv game.o lib/