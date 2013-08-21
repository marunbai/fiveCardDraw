all: main

main: list.o deck.o hand.o player.o card.h main.c
	gcc list.o deck.o hand.o player.o card.h main.c -o main 

deck.o: deck.c deck.h  
	gcc -c deck.c

list.o: list.c list.h
	gcc -c list.c

hand.o: hand.c hand.h
	gcc -c hand.c

player.o: player.c player.h
	gcc -c player.c
