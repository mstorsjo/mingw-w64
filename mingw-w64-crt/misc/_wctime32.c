/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>

static wchar_t *__cdecl emu__wctime32(const __time32_t *timeptr)
{
    return _wctime64(&(__time64_t){ *timeptr });
}

#define RETT wchar_t *
#define FUNC _wctime32
#define ARGS const __time32_t *timeptr
#define CALL timeptr
#include "msvcrt_or_emu_glue.h"
