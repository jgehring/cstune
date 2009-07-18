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
 */


#ifndef _PLAYER_H
#define _PLAYER_H


#include <string>
#include <vector>

#include <xine.h>
#include <xine/xineutils.h>

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
		player(char *startdir = NULL);
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
		void			set_volume(int volume);
		int 			get_volume();

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
