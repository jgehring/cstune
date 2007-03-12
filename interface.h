/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 */


#ifndef _INTERFACE_H
#define _INTERFACE_H


#include "player.h"


#define CMD_SIZE 2048


class player;


class interface
{
	public:
		interface(player *p);
		~interface();

		void		loop();

	private:
		void		interpret_exec(char *cmd);
		void		print_help(char *topic = " ");

		player		*p;
};


#endif

