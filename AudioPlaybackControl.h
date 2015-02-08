#ifndef _AUDIOPLAYBACKCONTROL_H_
#define _AUDIOPLAYBACKCONTROL_H_

/* ***************************************************************************
 * Macros
 * **************************************************************************/

#define EXIT_ON_ERROR(hres)  \
    if (FAILED(hres)) { goto Exit; }

#define SAFE_RELEASE(punk)  \
    if ((punk) != NULL) { (punk)->Release(); (punk) = NULL; }


/* ***************************************************************************
 * Include Files
 * **************************************************************************/

#include <windows.h>
#include <stdio.h>

/* Multimedia */
#include <mmreg.h>
#include <mmdeviceapi.h>
#include <FunctionDiscoveryKeys_devpkey.h>


/* ***************************************************************************
 * Functions
 * **************************************************************************/
 
HRESULT SetDefaultAudioPlaybackDevice( LPCWSTR );

void NextAudioPlaybackDevice( void );


#endif
