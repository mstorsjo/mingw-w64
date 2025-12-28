/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>

static char *__cdecl emu__ctime32(const __time32_t *timeptr)
{
    return _ctime64(&(__time64_t){ *timeptr });
}

#define RETT char *
#define FUNC _ctime32
#define ARGS const __time32_t *timeptr
#define CALL timeptr
#include "msvcrt_or_emu_glue.h"
