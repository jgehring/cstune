# Makefile for csTune

csTune: main.o interface.o player.o
	gcc -o csTune main.o interface.o player.o -lstdc++ -lxine -lreadline

main.o: main.cpp interface.h player.h
	gcc -c -o main.o -I. main.cpp

interface.o: interface.cpp interface.h player.h
	gcc -c -o interface.o -I. interface.cpp

player.o: player.cpp player.h interface.h
	gcc -c -o player.o -I. player.cpp

clean:
	rm *.o csTune
