/*****************************************************************************
 * .c: VLM interface plugin
 *****************************************************************************
 * Copyright (C) 2000, 2001 VideoLAN
 * $Id: vlm.h,v 1.1 2004/03/05 14:03:20 garf Exp $
 *
 * Authors: Simon Latapie <garf@videolan.org>
 *          Laurent Aimar <fenrir@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/* VLM specific - structures and functions */
enum
{
    VOD_TYPE = 0,
    BROADCAST_TYPE = 1,
};

typedef struct
{
    vlc_bool_t b_enabled;
    int      i_type;

    /* name "media" is reserved */
    char    *psz_name;

    int     i_input;
    char    **input;

    /* only for broadcast */
    vlc_bool_t b_loop;

    /* "playlist" index */
    int     i_index;

    char    *psz_output;

    int     i_option;
    char    **option;

    /* global options for all inputs */
    char    **input_option;
    int     i_input_option;
    input_thread_t  *p_input;

} vlm_media_t;


typedef struct
{
    /* names "schedule" is reserved */
    char    *psz_name;
    vlc_bool_t b_enabled;
    /* list of commands to execute on date */
    int i_command;
    char **command;

    /* the date of 1st execution */
    mtime_t i_date;

    /* if != 0 repeat schedule every (period) */
    mtime_t i_period;
    /* number of times you have to repeat
       i_repeat < 0 : endless repeat     */
    int i_repeat;

} vlm_schedule_t;


typedef struct
{
    VLC_COMMON_MEMBERS

    vlc_mutex_t lock;

#if 0
    int         i_vod;
    vlm_media_t **vod;

    int         i_broadcast;
    vlm_media_t **broadcast;
#endif

    int            i_media;
    vlm_media_t    **media;

    int            i_schedule;
    vlm_schedule_t **schedule;
} vlm_t;


#define vlm_New( a ) __vlm_New( VLC_OBJECT(a) )
vlm_t *__vlm_New ( vlc_object_t * );
void   vlm_Delete( vlm_t * );

int vlm_ExecuteCommand( vlm_t *, char *, char **);
