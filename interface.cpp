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


// Toggles random mode or displays current mode
void interface::toggle_random(char *onoff)
{
	if (onoff && strlen(onoff))
	{
		++onoff;
		if (!strcmp(onoff, "on"))
		{
			p->set_random(true);
		}
		else if (!strcmp(onoff, "off"))
		{
			p->set_random(false);
		}
		else
		{
			cout << "Please specifiy either 'on' or 'off'. See 'help rand' for details" << endl;
		}
	}
	else
	{
		cout << "Random mode is " << (p->random() ? "on" : "off") << endl;
	}
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
	else if (check_cmd(cmd, "next", "n", true))
	{
		if (sep_pos && strlen(sep_pos))
			p->next_song(atoi(++sep_pos));
		else
			p->next_song();
	}
	else if (check_cmd(cmd, "showpl", "sp"))
	{
		p->show_playlist();
	}
	else if (check_cmd(cmd, "jump", "j", true))
	{
		if (sep_pos && strlen(sep_pos))
			p->jump(++sep_pos);
		else
			cout << "No regular expression specified. See 'help jump' for details" << endl;
	}
	else if (check_cmd(cmd, "filter", "fl", true))
	{
		if (sep_pos && strlen(sep_pos))
			p->filter(++sep_pos);
		else
			cout << "No regular expression speficied. See 'help filter' for details" << endl;
	}
	else if (check_cmd(cmd, "rand", "r", true))
	{
		toggle_random(sep_pos);
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
		cout << "\tJumps n tracks forward/backward\n\n";
		cout << "If the 'num' argument is not given, it will be interpreted as\n";
		cout << "'1' (i.e. the next song in the playlist will be played)\n";
		cout << "If 'num' is < 0, csTune will jump backwards, i.e. '-1' for the\n";
		cout << "previous track\n";
	}
	else if (check_cmd(topic, "showpl", "sp"))
	{
		cout << "\tshowpl\n";
		cout << "\tShows the current playlist\n\n";
		cout << "'showpl' writes the current playlist to a temporary file and\n";
		cout << "less inside the terminal to display the playlist.\n";
		cout << "If you want to edit the playlist, use 'edit'\n";
	}
	else if (check_cmd(topic, "jump", "j"))
	{
		cout << "\tjump <regexp>\n";
		cout << "\tJumps to track that matches a given regular expression\n\n";
		cout << "csTune starts searching at the current track and searches the playlist\n";
		cout << "for the given regular expression. If the search has been successfull,\n";
		cout << "it starts playing the first track it has found.\n";
	}
	else if (check_cmd(topic, "filter", "fl"))
	{
		cout << "\tfilter <regexp>\n";
		cout << "\tFilters the playlist with a regular expression\n\n";
		cout << "After filtering, the playlist will only contain the tracks that\n";
		cout << "were matching the given regular expression.\n";
		cout << "If no tracks are matching the regex, no filter will be applied.\n";
	}
	else if (check_cmd(topic, "rand", "r"))
	{
		cout << "\trand [on|off]\n";
		cout << "\tTurn on/off random or show current status\n\n";
		cout << "If arguments are omitted, 'rand' shows the current state of the\n";
		cout << "random switch. Use 'on' or 'off' to turn it on or off\n";
	}
	else
	{
		cout << "Available commands (shortcuts):\n";
		cout << "\tplay\t(p)\n\tstart\t(s)\n\tstop\t(st)\n\tpause\t(ps)\n";
		cout << "\tnext\t(n)\n\tjump\t(j)\n\tshowpl\t(sp)\n\trand\t(r)\n\tfilter\t(fl)\n\tquit\t(q)\n\thelp\t(h)\n";
		cout << "Type 'help <command>' for specific help\n";
	}

	cout << endl;
}


