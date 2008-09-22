/*
 * 	cstune - A simple command line audio player
 * 	CopyLeft 2007 by Jonas Gehring
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
