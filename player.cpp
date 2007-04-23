/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 */


#include <iostream>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <regex.h>

#include "player.h"


using namespace std;


// Constructor
player::player()
{
	playing_st = open_st = init_st = random_st = false;
	current_track = 0;

	xine_engine = NULL;
	xine_stream = NULL;
	xine_port = NULL;
	xine_queue = NULL;

	init_xine();
}


// Destructor
player::~player()
{
	if (open_st)
	{
		stop();
	}
	xine_event_dispose_queue(xine_queue);
	xine_dispose(xine_stream);
	if (xine_port)
	{
		xine_close_audio_driver(xine_engine, xine_port); 
	}
	xine_exit(xine_engine);
}


// Status information
bool player::initialized()
{
	return init_st;
}
bool player::playing()
{
	return playing_st;
}
bool player::stream_open()
{
	return open_st;
}
bool player::random()
{
	return random_st;
}


// Plays the song at a given location
int player::play(char *path)
{
	// Clear playlist
	playlist.clear();
	current_track = 0;

	// Strip whitespaces at the end of the path
	char *ptr = path + strlen(path) - 1;
	while (*ptr == ' ')
	{
		*ptr = 0x00;
		ptr--;
	}

	// Enqueue path
	struct stat st;
	stat(path, &st);
	if (st.st_mode & S_IFDIR)
	{
		enqueue_dir(path);
	}
	else if (st.st_mode & S_IFREG)
	{
		enqueue_loc(path);
	}
	else
	{
		cout << "Sorry, URLS are not supported atm" << endl;
	}

	stop();

	if (playlist.empty())
	{
		cout << "Sorry, no media was found at \"" << path << "\"" << endl;
		return NO_FILES_FOUND;
	}

	XTERM_GREEN;
	cout << ">> Added " << playlist.size() << " track";
	cout << (playlist.size() > 1 ? "s " : " ") << "to playlist" << endl; 
	XTERM_WHITE;

	playing_st = false;
	return start();
}


// Starts playing 
int player::start()
{
	stop();

	if (!xine_open(xine_stream, playlist[current_track].c_str()))
	{
		XTERM_RED;
		cout << ">> ERRR opening " << playlist[current_track] << endl;
		XTERM_WHITE;
		return CANNOT_OPEN_STREAM;
	}

	if (!xine_play(xine_stream, 0, 0))
	{
		XTERM_RED;
		cout << ">> ERROR playing " << playlist[current_track] << endl;
		XTERM_WHITE;
		return CANNOT_PLAY_FILE;
	}

	playing_st = open_st = true;
	XTERM_GREEN;
	cout << ">> Now playing: " << playlist[current_track] << endl;
	XTERM_WHITE;
	return 0;
}


// Stops playing
void player::stop()
{
	if (open_st)
	{
		xine_close(xine_stream);
		playing_st = open_st = false;
	}
}


// Toggles pause
void player::toggle_pause()
{
	if (open_st == false)
	{
		cout << ">> No stream to pause. Please use 'start' first" << endl;
		return;
	}
	playing_st ? pause() : resume();
}


// Plays the next song
void player::next_song(int n)
{
	if (n < 1) n = 1;
	stop();
	if (random_st == false)
	{
		current_track = (current_track+n) % playlist.size();
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			current_track = (rand() * clock()) % playlist.size();
		}
	}
	start();
}


// Opens less to show the current playlist
void player::show_playlist()
{
	// Check for length of playlist
	if (playlist.size() == 0)
	{
		cout << "No elements in playlist" << endl;
		return;
	}

	// Write current playlist to temporary file
	ofstream out;
	char temp[2048];
	sprintf(temp, "%s%s", xine_get_homedir(), "/.cst_playlist");
	
	out.open(temp);
	if (out.good() == false)
	{
		XTERM_RED;
		cout << ">> ERROR: Unable to write to temporary playlist file" << endl;
		XTERM_WHITE
		return;
	}

	for (unsigned int i = 0; i < playlist.size(); i++)
	{
		out << playlist[i] << endl;
	}

	out.close();
	char cmd[2048+5];
	strcpy(cmd, "less ");
	strcat(cmd, temp);
	system(cmd);
	unlink(temp);
}


// Jumps to the first song that matches string
void player::jump(char *string)
{
	regex_t regex;
	if (regcomp(&regex, string, REG_ICASE | REG_NOSUB))
	{
		cout << "ERROR: Invalid regular expression." << endl;
		return;
	}
	for (unsigned int i = 0; i < playlist.size(); i++)
	{
		current_track = ++current_track % playlist.size();
		if (regexec(&regex, playlist[current_track].c_str(), 0, NULL, 0) == 0)
		{
			stop();
			start();
			regfree(&regex);
			return;
		}
	}
	regfree(&regex);

	cout << "Sorry, " << string << " does not occur in the current playlist" << endl;
}


// Filters the playlist
void player::filter(char *string)
{
	regex_t regex;
	if (regcomp(&regex, string, REG_ICASE | REG_NOSUB))
	{
		cout << "ERROR: Invalid regular expression." << endl;
		return;
	}
	std::vector<std::string> new_list;
	for (unsigned int i = 0; i < playlist.size(); i++)
	{
		if (regexec(&regex, playlist[i].c_str(), 0, NULL, 0) == 0)
		{
			new_list.push_back(playlist[i]);
		}
	}
	regfree(&regex);

	if (new_list.size())
	{
		current_track = -1;	// FIXME: Repeat? Previous track?
		cout << "Filtered " << new_list.size() << " of " << playlist.size() << " tracks" << endl;
		playlist = new_list;
		return;
	}

	cout << "Sorry, " << string << " does not occur in the current playlist" << endl;
}


// Sets random mode
void player::set_random(bool rand)
{
	random_st = rand;
}


// Pause playing
void player::pause()
{
	if (open_st)
	{
		xine_set_param(xine_stream, XINE_PARAM_SPEED, XINE_SPEED_PAUSE);
		playing_st = false;
	}
}


// Resume playing
void player::resume()
{
	if (open_st)
	{
		xine_set_param(xine_stream, XINE_PARAM_SPEED, XINE_SPEED_NORMAL);
		playing_st = true;
	}
}


// Enqueues a directory of media files
void player::enqueue_dir(const char *path)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (dir != NULL)
	{
		char filename[4096];
		while ((entry = readdir(dir)))
		{
			if (strncmp(entry->d_name, ".", 1) && strcmp(entry->d_name, ".."))
			{
				sprintf(filename, "%s/%s", path, entry->d_name); 
				struct stat st;
				stat(filename, &st);
				if (st.st_mode & S_IFDIR)
				{
					enqueue_dir(filename);
				}
				else if (st.st_mode & S_IFREG)
				{
					enqueue_loc(filename);
				}
			}
		}

		closedir(dir);
	}
}


// Enqueues a location
void player::enqueue_loc(const char *path)
{
	playlist.push_back(string(path));
}


// Initializes the xine engine
void player::init_xine()
{
	char configfile[4096];

	xine_engine = xine_new();
	sprintf(configfile, "%s%s", xine_get_homedir(), "./xine/config");
	xine_config_load(xine_engine, configfile);
	xine_init(xine_engine);

#ifdef _OSX_
	xine_port = xine_open_audio_driver(xine_engine, "esd", NULL);
#else
	xine_port = xine_open_audio_driver(xine_engine, "auto", NULL);
#endif
	xine_stream = xine_stream_new(xine_engine, xine_port, NULL);
	xine_queue = xine_event_new_queue(xine_stream);

	xine_event_create_listener_thread(xine_queue, &xine_event_listener, this);

	init_st = true;
}


// Listen for xine events
void player::xine_event_listener(void *user_data, const xine_event_t *event)
{
	player *instance = static_cast<player *>(user_data);

	switch (event->type)
	{
		case XINE_EVENT_UI_PLAYBACK_FINISHED:
			cout << endl;
			instance->next_song();
			cout << "> " << flush;
			break;

		default:
			break;
	}
}


