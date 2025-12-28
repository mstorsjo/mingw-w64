/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <sys/timeb.h>

static void __cdecl emu__ftime32(struct __timeb32 *tb32)
{
    struct __timeb64 tb64;
    _ftime64(&tb64);
    tb32->time = (__time32_t)tb64.time; /* truncate */
    tb32->millitm = tb64.millitm;
    tb32->timezone = tb64.timezone;
}

#define RETT void
#define FUNC _ftime32
#define ARGS struct __timeb32 *tb
#define CALL tb
#include "msvcrt_or_emu_glue.h"
