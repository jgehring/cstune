/*
 * 	cstune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 *
 *
 *	Arguments:
 *	<dir> 	-	startup with all files from dir in playlist
 */

#include <iostream>
#include <string>

#include "player.h"
#include "interface.h"


using namespace std;


// Program entry point
int main(int argc, char **argv)
{
	char *startdir = NULL;
	
	if (argc > 1)
	{
		startdir = argv[1];
	}

	player *p = new player(startdir);
	interface *i = new interface(p);

	i->loop();

	delete i;
	delete p;
}


