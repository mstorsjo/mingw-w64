/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>
#include <stdint.h>
#include <errno.h>

static __time32_t __cdecl emu__mktime32(struct tm *tmptr)
{
    struct tm tmbuf = *tmptr;
    __time64_t time64 = _mktime64(&tmbuf);
    if (time64 == -1)
        return -1;
    if (time64 < 0 || time64 > INT32_MAX) {
        errno = EINVAL;
        return -1;
    }
    *tmptr = tmbuf;
    return (__time32_t)time64;
}

#define RETT __time32_t
#define FUNC _mktime32
#define ARGS struct tm *tmptr
#define CALL tmptr
#include "msvcrt_or_emu_glue.h"
