/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <utime.h>
#include <stddef.h>

static int __cdecl emu__futime32(int fd, struct __utimbuf32 *times)
{
    return _futime64(fd, times ? &(struct __utimbuf64){ .actime = times->actime, .modtime = times->modtime } : NULL);
}

#define RETT int
#define FUNC _futime32
#define ARGS int fd, struct __utimbuf32 *times
#define CALL fd, times
#include "msvcrt_or_emu_glue.h"
