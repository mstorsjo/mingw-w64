/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <math.h>

void sincos(double x, double *s, double *c)
{
    *s = sin(x);
    *c = cos(x);
}
