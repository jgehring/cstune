/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 */


#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>

#include "interface.h"


using namespace std;


static int user_cmd;


// Constructor
interface::interface(player *p)
	:	p(p)
{

}


// Destructor
interface::~interface()
{

}


// Main loop
void interface::loop()
{
	XTERM_WHITE;
	char *cmd = new char[CMD_SIZE + 1];

	do
	{
		cmd[0] = 0x00;
		char *c = readline("> ");
		
		if (!(c) && !(*c))
		{
			cout << endl;	
			continue;
		}

		strcpy(cmd, c);

		interpret_exec(cmd);
	}
	while (strcmp(cmd, "q") && strcmp(cmd, "quit"));

	delete cmd;
}


// Checks for a command
bool interface::check_cmd(char *cmd, const char *check, const char *sc, bool args)
{
	if (!strcmp(cmd, check) || !strcmp(cmd, sc))
		return true;
	if (args)
	{
		int len = strlen(check), lens = strlen(sc);
		char tmp[len+2]; strcpy(tmp, check); strcat(tmp, " ");
		char tmps[lens+2]; strcpy(tmps, sc); strcat(tmps, " ");
		if (!strncmp(cmd, tmp, len+1) || !strncmp(cmd, tmps, lens+1))
			return true;
	}

	return false;
}



// Interprets and executes a command
void interface::interpret_exec(char *cmd)
{
	char* sep_pos = strchr(cmd, ' ');
	if (check_cmd(cmd, "help", "h", true))
	{
		if (sep_pos && strlen(sep_pos))
			print_help(++sep_pos);
		else
			print_help();
	}
	else if (check_cmd(cmd, "pause", "ps"))
	{
		p->toggle_pause();
	}
	else if (check_cmd(cmd, "play", "p", true))
	{
		if (sep_pos && strlen(sep_pos))
			p->play(++sep_pos);
		else
			cout << "No location specified. See 'help play' for details" << endl;	
	}
	else if (check_cmd(cmd, "start", "s"))
	{
		p->start();
	}
	else if (check_cmd(cmd, "stop", "st"))
	{
		p->stop();
	}
	else if (check_cmd(cmd, "next", "n"))
	{
		p->next_song(atoi(sep_pos));
	}
	else if (check_cmd(cmd, "showpl", "sp"))
	{
		p->show_playlist();
	}
	else if (!check_cmd(cmd, "quit", "q") && strlen(cmd))
	{
		cout << "Unkown command '" << cmd << "'. Enter 'help' for a list of available commands" << endl;
	}
}


// Prints help screen with available commands
void interface::print_help(char *topic)
{
	cout << endl;

	if (check_cmd(topic, "quit", "q"))
	{
		cout << "\tquit\n";
		cout << "\tTerminates the program\n\n";
		cout << "You should use this command rather than Ctrl-C to avoid memory\n";
		cout << "leaks.\n";
	}
	else if (check_cmd(topic, "play", "p"))
	{
		cout << "\tplay <location>\n";
		cout << "\tPlays the media at the given location\n\n";
		cout << "The media can be a file, an url or a directory. If\n";
		cout << "it is a directory, all files in it will be enqueued\n";
		cout << "into a new playlist\n";
	}
	else if (check_cmd(topic, "next", "n"))
	{
		cout << "\tnext [num]\n";
		cout << "\tJumps n tracks forward\n\n";
		cout << "If the 'num' argument is not given, it will be interpreted as\n";
		cout << "'1' (i.e. the next song in the playlist will be played)\n";
	}
	else if (check_cmd(topic, "showpl", "sp"))
	{
		cout << "\tshowpl\n";
		cout << "\tShows the current playlist\n\n";
		cout << "'showpl' writes the current playlist to a temporary file and\n";
		cout << "less inside the terminal to display the playlist.\n";
		cout << "If you want to edit the playlist, use 'edit'\n";
	}
	else
	{
		cout << "Available commands (shortcuts):\n";
		cout << "\tplay\t(p)\n\tstart\t(st)\n\tstop\t(s)\n\tpause\t(ps)\n";
		cout << "\tnext\t(n)\n\tshowpl\t(sp)\n\tquit\t(q)\n\thelp\t(h)\n";
		cout << "Type 'help <command>' for specific help\n";
	}

	cout << endl;
}


