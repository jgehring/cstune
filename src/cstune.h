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


#ifndef _CSTUNE_H
#define _CSTUNE_H


#include <stdio.h>

#ifdef HAVE_CONFIG_H
 #include "config.h"
#else
 #error "No config.h"
#endif


// Macros for outputting colored text
#ifdef HAVE_COLORS
 #define XTERM_GREEN	printf("\033[0;32m");
 #define XTERM_WHITE	printf("\033[0;37m");
 #define XTERM_RED	printf("\033[0;31m");
#else
 #define XTERM_GREEN
 #define XTERM_WHITE
 #define XTERM_RED
#endif


#endif
