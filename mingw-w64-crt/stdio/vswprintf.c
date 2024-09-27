/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#define __CRT__NO_INLINE
#include <stdarg.h>
#include <stdio.h>

int __cdecl __ms_vswprintf(wchar_t *__restrict__ ws, size_t n, const wchar_t *__restrict__ format, va_list arg)
{
    int retval;

    retval = _vsnwprintf(ws, n-1, format, arg);

    /* _vsnwprintf() does not fill trailing nul wide char if there is not place for it */
    if (retval < 0 || (size_t)retval == n-1)
        ws[n-1] = L'\0';

    return retval;
}
