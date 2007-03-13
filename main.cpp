/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 */


#include <iostream>
#include <string>

#include "player.h"
#include "interface.h"


using namespace std;


// Program entry point
int main(int argc, char **argv)
{
	// TODO: Parse command line arguments, output help etc.
	player *p = new player();
	interface *i = new interface(p);

	i->loop();

	delete i;
	delete p;
}


