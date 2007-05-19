# Makefile for csTune


TARGET			=	csTune
CXX_FLAGS		=	-Wall -O2 -Wno-deprecated -g
INCLUDE_PATH		=	-I.
INCLUDE_PATH_OSX	=	$(INCLUDE_PATH) -I/sw/include
FLAGS_OSX		=	`/sw/bin/xine-config --cflags` `/sw/bin/xine-config --libs`
LIBS			=	-lstdc++ -lxine -lreadline
LIBS_OSX		=	-L/sw/lib $(LIBS)
DEFINES_OSX		=	-D"_OSX_"


# Linux
csTune: main.o interface.o player.o
	gcc -o $(TARGET) main.o interface.o player.o $(LIBS) 
main.o: main.cpp interface.h player.h
	gcc -c $(CXX_FLAGS) -o main.o $(INCLUDE_PATH) main.cpp
interface.o: interface.cpp interface.h player.h
	gcc -c $(CXX_FLAGS) -o interface.o $(INCLUDE_PATH) interface.cpp
player.o: player.cpp player.h interface.h
	gcc -c $(CXX_FLAGS) -o player.o $(INCLUDE_PATH) player.cpp


# OS X
csTune.osx: mainosx.o interfaceosx.o playerosx.o
	c++  $(FLAGS_OSX) -o csTune main.o interface.o player.o $(LIBS_OSX) 
mainosx.o: main.cpp interface.h player.h
	gcc -c $(CXX_FLAGS) -o main.o $(INCLUDE_PATH_OSX) main.cpp
interfaceosx.o: interface.cpp interface.h player.h
	gcc -c $(CXX_FLAGS) -o interface.o $(INCLUDE_PATH_OSX) interface.cpp
playerosx.o: player.cpp player.h interface.h
	gcc -c $(CXX_FLAGS) -o player.o $(DEFINES_OSX) $(INCLUDE_PATH_OSX) player.cpp

clean:
	rm *.o csTune
