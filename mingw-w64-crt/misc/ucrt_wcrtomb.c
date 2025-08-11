/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#undef __MSVCRT_VERSION__
#define _UCRT

#include "wcrtomb.c"

static size_t __cdecl wcrtomb_init (char *__restrict__, wchar_t, mbstate_t *__restrict__);
static size_t __cdecl wcsrtombs_init (char *__restrict__, const wchar_t **__restrict__, size_t, mbstate_t *__restrict__);

typedef size_t (__cdecl *volatile __wcrtomb_t) (char *__restrict__, wchar_t, mbstate_t *__restrict__);
typedef size_t (__cdecl *volatile __wcsrtombs_t) (char *__restrict__, const wchar_t **__restrict__, size_t, mbstate_t *__restrict__);

static __wcrtomb_t __wcrtomb = wcrtomb_init;
static __wcsrtombs_t __wcsrtombs = wcsrtombs_init;

static size_t wcrtomb_init (
  char *__restrict__ mbc,
  wchar_t wc,
  mbstate_t *__restrict__ state
) {
  HANDLE ucrt = LoadLibraryW (L"ucrtbase.dll");

  if (ucrt == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain handle to ucrtbase.dll\n");
    abort ();
  }

  __wcrtomb_t real_wcrtomb = (__wcrtomb_t) GetProcAddress (ucrt, "wcrtomb");

  if (real_wcrtomb == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain address of wcrtomb function\n");
    abort ();
  }

  InterlockedExchangePointer ((PVOID volatile *) &__wcrtomb, (PVOID) real_wcrtomb);
  FreeLibrary (ucrt);

  return __wcrtomb (mbc, wc, state);
}

static size_t wcsrtombs_init (
  char *__restrict__ mbs,
  const wchar_t **__restrict__ wcs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  HANDLE ucrt = LoadLibraryW (L"ucrtbase.dll");

  if (ucrt == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain handle to ucrtbase.dll\n");
    abort ();
  }

  __wcsrtombs_t real_wcsrtombs = (__wcsrtombs_t) GetProcAddress (ucrt, "wcsrtombs");

  if (real_wcsrtombs == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain address of wcsrtombs function\n");
    abort ();
  }

  InterlockedExchangePointer ((PVOID volatile *) &__wcsrtombs, (PVOID) real_wcsrtombs);
  FreeLibrary (ucrt);

  return __wcsrtombs (mbs, wcs, count, state);
}

size_t __cdecl wcrtomb (
  char *__restrict__ mbc,
  wchar_t wc,
  mbstate_t *__restrict__ state
) {
  if (MB_CUR_MAX > 2) {
    return __wcrtomb (mbc, wc, state);
  }
  return __mingw_wcrtomb (mbc, wc, state);
}

size_t __cdecl wcsrtombs (
  char *__restrict__ mbs,
  const wchar_t **__restrict__ wcs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  if (MB_CUR_MAX > 2) {
    return __wcsrtombs (mbs, wcs, count, state);
  }
  return __mingw_wcsrtombs (mbs, wcs, count, state);
}
