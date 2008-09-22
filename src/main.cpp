/*
 * 	cstune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 *
 *
 *	Arguments:
 *	--version
 *	--help [-h]
 *	<dir> 	-	startup with all files from dir in playlist
 */

#include <iostream>
#include <string>

#include "cstune.h"
#include "player.h"
#include "interface.h"


using namespace std;


// Program entry point
int main(int argc, char **argv)
{
	char *startdir = NULL;
	
	if (argc > 1)
	{
		if (!strcmp(argv[1], "--version"))
		{
			cout << PACKAGE_NAME << " " << PACKAGE_VERSION << endl;
			return EXIT_SUCCESS;
		}
		else if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
		{
			cout << PACKAGE_NAME << " " << PACKAGE_VERSION << endl;
			cout << "CopyLeft 2008 by Jonas Gehring <" << PACKAGE_BUGREPORT
				<< ">" << endl << endl;
			cout << "For in-program help, start the program and run 'help'" << endl;
			return EXIT_SUCCESS;
		}

		startdir = argv[1];
	}

	player *p = new player(startdir);
	interface *i = new interface(p);

	i->loop();

	delete i;
	delete p;
}
