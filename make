#!/bin/sh
#	Simple make-script (too lazy to write a Makefile)

rm csTune
gcc -c -o main.o -lstdc++ -I. -pthread main.cpp 
gcc -c -o interface.o -lstdc++ -I. -pthread interface.cpp 
gcc -c -o player.o -lstdc++ -I. -pthread player.cpp 
gcc -o csTune -lstdc++ -lxine main.o interface.o player.o
