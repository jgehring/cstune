/*
 * 	cstune - A simple command line audio player
 * 	Copyright (C) 2007-2009 Jonas Gehring
 * 	All rights reserved.
 *
 * 	Redistribution and use in source and binary forms, with or without
 * 	modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 * 	      notice, this list of conditions and the following disclaimer.
 * 	    * Redistributions in binary form must reproduce the above copyright
 * 	      notice, this list of conditions and the following disclaimer in the
 * 	      documentation and/or other materials provided with the distribution.
 * 	    * Neither the name of the copyright holders nor the
 * 	      names of its contributors may be used to endorse or promote products
 * 	      derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
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
