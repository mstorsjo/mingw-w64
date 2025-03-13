/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
long double atanl (long double x);
double atan (double x);

long double
atanl (long double x)
{
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
  return atan (x);
#else
  long double res = 0.0L;

  asm volatile (
       "fld1\n\t"
       "fpatan"
       : "=t" (res) : "0" (x));
  return res;
#endif
}
