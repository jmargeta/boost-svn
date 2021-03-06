/*
 * Copyright 2002. Vladimir Prus
 * Copyright 2005. Rene Rivera
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "jam.h"
#include "pwd.h"

#include "mem.h"
#include "object.h"
#include "pathsys.h"

#include <errno.h>
#include <limits.h>

/* MinGW on Windows declares PATH_MAX in limits.h */
#if defined(NT) && !defined(__GNUC__)
# include <direct.h>
# define PATH_MAX _MAX_PATH
#else
# include <unistd.h>
# if defined(__COMO__)
#  include <linux/limits.h>
# endif
#endif

#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

/* The current directory can not change in Boost Jam, so optimize pwd() by
 * caching the result.
*/
static OBJECT * pwd_result;


LIST * pwd( void )
{
    if ( !pwd_result )
    {
        int buffer_size = PATH_MAX;
        char * result_buffer = 0;
        int error;
        do
        {
            char * const buffer = BJAM_MALLOC_RAW( buffer_size );
            result_buffer = getcwd( buffer, buffer_size );
            error = errno;
            if ( result_buffer )
            {
                /* We return the path using its canonical/long/key format. */
                OBJECT * const result = object_new( result_buffer );
                pwd_result = path_as_key( result );
                object_free( result );
            }
            buffer_size *= 2;
            BJAM_FREE_RAW( buffer );
        }
        while ( !pwd_result && error == ERANGE );

        if ( !pwd_result )
        {
            perror( "can not get current directory" );
            return L0;
        }
    }
    return list_new( object_copy( pwd_result ) );
}


void pwd_done( void )
{
    if ( pwd_result )
    {
        object_free( pwd_result );
    }
}
