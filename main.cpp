/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 *
 *
 *	Arguments:
 *	 -p <dir> 	-	startup with all files from dir in playlist
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
	
	for (int i = 1; i < argc; i++)
	{
		if (!strncmp("-p", argv[i], 2) && argc >= ++i)
		{
			startdir = argv[i];
		}
	}
	
	player *p = new player(startdir);
	interface *i = new interface(p);

	i->loop();

	delete i;
	delete p;
}


