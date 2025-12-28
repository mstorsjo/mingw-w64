/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>

static struct tm *__cdecl emu__gmtime32(const __time32_t *timeptr)
{
    return _gmtime64(&(__time64_t){ *timeptr });
}

#define RETT struct tm *
#define FUNC _gmtime32
#define ARGS const __time32_t *timeptr
#define CALL timeptr
#include "msvcrt_or_emu_glue.h"
