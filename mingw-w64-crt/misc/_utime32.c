/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <utime.h>
#include <stddef.h>

static int __cdecl emu__utime32(const char *filename, struct __utimbuf32 *times)
{
    return _utime64(filename, times ? &(struct __utimbuf64){ .actime = times->actime, .modtime = times->modtime } : NULL);
}

#define RETT int
#define FUNC _utime32
#define ARGS const char *filename, struct __utimbuf32 *times
#define CALL filename, times
#include "msvcrt_or_emu_glue.h"
