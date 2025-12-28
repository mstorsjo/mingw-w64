/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>
#include <stdint.h>

static __time32_t __cdecl emu__time32(__time32_t *timeptr)
{
    __time64_t time64 = _time64(NULL);
    if (time64 > INT32_MAX)
        time64 = -1;
    if (timeptr)
        *timeptr = (__time32_t)time64;
    return (__time32_t)time64;
}

#define RETT __time32_t
#define FUNC _time32
#define ARGS __time32_t *timeptr
#define CALL timeptr
#include "msvcrt_or_emu_glue.h"
