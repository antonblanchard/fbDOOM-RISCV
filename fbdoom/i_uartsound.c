//
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Output samples over UART
//

#include <string.h>

#include "doomtype.h"

#include "deh_str.h"
#include "i_sound.h"
#include "m_misc.h"
#include "w_wad.h"
#include "z_zone.h"

static boolean use_sfx_prefix;

static int I_UART_StartSound(sfxinfo_t *sfxinfo,
                            int channel,
                            int vol,
                            int sep)
{
    printf("P%d\n", sfxinfo->lumpnum);

    return 1;
}

static void I_UART_StopSound(int handle)
{
    // no-op.
}

//
// Retrieve the raw data lump index
//  for a given SFX name.
//

static int I_UART_GetSfxLumpNum(sfxinfo_t* sfx)
{
    char namebuf[9];

    if (use_sfx_prefix)
    {
        M_snprintf(namebuf, sizeof(namebuf), "dp%s", DEH_String(sfx->name));
    }
    else
    {
        M_StringCopy(namebuf, DEH_String(sfx->name), sizeof(namebuf));
    }

    return W_GetNumForName(namebuf);
}


static boolean I_UART_SoundIsPlaying(int handle)
{
    return false;
}

static boolean I_UART_InitSound(boolean _use_sfx_prefix)
{
    use_sfx_prefix = _use_sfx_prefix;
    return true;
}

static void I_UART_ShutdownSound(void)
{
    // no-op.
}

static void I_UART_UpdateSound(void)
{
    // no-op.
}

void I_UART_UpdateSoundParams(int channel, int vol, int sep)
{
    // no-op.
}

static snddevice_t sound_uart_devices[] = 
{
    SNDDEVICE_UART,
};

sound_module_t sound_uart_module = 
{
    sound_uart_devices,
    arrlen(sound_uart_devices),
    I_UART_InitSound,
    I_UART_ShutdownSound,
    I_UART_GetSfxLumpNum,
    I_UART_UpdateSound,
    I_UART_UpdateSoundParams,
    I_UART_StartSound,
    I_UART_StopSound,
    I_UART_SoundIsPlaying,
};
