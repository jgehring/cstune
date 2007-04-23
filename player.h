/*
 * 	csTune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
 */


#ifndef _PLAYER_H
#define _PLAYER_H


#include <string>
#include <vector>

#include <xine.h>
#include <xine/xineutils.h>

#include "csTune.h"
#include "interface.h"


enum error_codes
{
	NO_FILES_FOUND = 1,
	CANNOT_OPEN_STREAM,
	CANNOT_PLAY_FILE,
	PLAYLIST_EMPTY
};


class player
{
	public:
		player();
		~player();

		bool			initialized();
		bool			playing();
		bool			stream_open();
		bool			random();

		int			play(char *path);
		int			start();
		void			stop();
		void			toggle_pause();
		void			next_song(int n = 1);
		void			show_playlist();
		void			jump(char *string);
		void			filter(char *string);
		void			set_random(bool rand);

	private:
		void			pause();
		void			resume();
		void			enqueue_dir(const char *path);
		void			enqueue_loc(const char *path);
		void			init_xine();
		static void		xine_event_listener(void *user_data, const xine_event_t *event);

		std::vector<std::string>	playlist;
		bool			playing_st, open_st, init_st, random_st;
		int			current_track;
		xine_t			*xine_engine;
		xine_stream_t		*xine_stream;
		xine_audio_port_t	*xine_port;
		xine_event_queue_t	*xine_queue;
};


#endif

