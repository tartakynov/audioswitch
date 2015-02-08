#ifndef _AUDIOSWITCH_H_
#define _AUDIOSWITCH_H_

/* ***************************************************************************
 * Macros
 * **************************************************************************/

 /* Exclude redundant APIs such as Cryptography, DDE, RPC, Shell, and Windows Sockets. */
#define WIN32_LEAN_AND_MEAN

/* Window class name for the window. */
#define WINDOW_CLASS_NAME "AudioSwitchWindow"


/* ***************************************************************************
 * Include Files
 * **************************************************************************/

#include <windows.h>
#include <wchar.h>

/* For attached console. */
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <locale.h>


/* ***************************************************************************
 * Functions
 * **************************************************************************/
 
LRESULT CALLBACK KeyboardProc( int, WPARAM, LPARAM );

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );


#endif
