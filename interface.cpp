/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 */


#include <iostream>
#include <stdlib.h>
#include <string.h>

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
		cout << "> ";
		cin.getline(cmd, CMD_SIZE);
		interpret_exec(cmd);
	}
	while (strcmp(cmd, "q") && strcmp(cmd, "quit"));

	delete cmd;
}


// Interprets and executes a command
void interface::interpret_exec(char *cmd)
{
	char* sep_pos = strchr(cmd, ' ');
	if (!strncmp(cmd, "help", 4) || !strncmp(cmd, "h", 1))
	{
		if (sep_pos && strlen(sep_pos))
			print_help(++sep_pos);
		else
			print_help();
	}
	else if (!strncmp(cmd, "play", 4) || !strncmp(cmd, "p", 1))
	{
		if (sep_pos && strlen(sep_pos))
			p->play(++sep_pos);
		else
			cout << "No location specified. See 'help play' for details" << endl;	
	}
	else if (!strcmp(cmd, "start") || !strcmp(cmd, "st"))
	{
		p->start();
	}
	else if (!strcmp(cmd, "stop") || !strcmp(cmd, "s"))
	{
		p->stop();
	}
	else if (!strcmp(cmd, "pause") || !strcmp(cmd, "ps"))
	{
		p->toggle_pause();
	}
	else if (!strcmp(cmd, "next") || !strcmp(cmd, "n"))
	{
		p->next_song();
	}
	else if (strcmp(cmd, "quit") && strcmp(cmd,"q"))
	{
		cout << "Unkown command. Enter 'help' for a list of available commands" << endl;
	}
}


// Prints help screen with available commands
void interface::print_help(char *topic)
{
	cout << endl;

	if (!strcmp(topic, "quit") || !strcmp(topic, "q"))
	{
		cout << "\tquit\n";
		cout << "\tTerminates the program\n\n";
		cout << "You should use this command rather than Ctrl-C to avoid memory\n";
		cout << "leaks.\n";
	}
	else if (!strcmp(topic, "play") || !strcmp(topic, "p"))
	{
		cout << "\tplay <location>\n";
		cout << "\tPlays the media at the given location\n\n";
		cout << "The media can be a file, an url or a directory. If\n";
		cout << "it is a directory, all files in it will be enqueued\n";
		cout << "into a new playlist\n";
	}
	else
	{
		cout << "Available commands (shortcuts):\n";
		cout << "\tplay\t(p)\n\tstart\t(st)\n\tstop\t(s)\n\tpause\t(ps)\n";
		cout << "\tnext\t(n)\n\tquit\t(q)\n\thelp\t(h)\n";
		cout << "Type 'help <command>' for specific help\n";
	}

	cout << endl;
}


