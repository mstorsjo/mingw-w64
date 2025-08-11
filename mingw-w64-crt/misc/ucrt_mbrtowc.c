/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#undef __MSVCRT_VERSION__
#define _UCRT

#include "mbrtowc.c"

static size_t __cdecl mbrlen_init (const char *__restrict__, size_t, mbstate_t *__restrict__);
static size_t __cdecl mbrtowc_init (wchar_t *__restrict__, const char *__restrict__, size_t, mbstate_t *__restrict__);
static size_t __cdecl mbsrtowcs_init (wchar_t *__restrict__, const char **__restrict__, size_t, mbstate_t *__restrict__);

typedef size_t (__cdecl *volatile __mbrlen_t) (const char *__restrict__, size_t, mbstate_t *__restrict__);
typedef size_t (__cdecl *volatile __mbrtowc_t) (wchar_t *__restrict__, const char *__restrict__, size_t, mbstate_t *__restrict__);
typedef size_t (__cdecl *volatile __mbsrtowcs_t) (wchar_t *__restrict__, const char **__restrict__, size_t, mbstate_t *__restrict__);

static __mbrlen_t __mbrlen = mbrlen_init;
static __mbrtowc_t __mbrtowc = mbrtowc_init;
static __mbsrtowcs_t __mbsrtowcs = mbsrtowcs_init;

static size_t mbrlen_init (
  const char *__restrict__ mbs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  HANDLE ucrt = LoadLibraryW (L"ucrtbase.dll");

  if (ucrt == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain handle to ucrtbase.dll\n");
    abort ();
  }

  __mbrlen_t real_mbrlen = (__mbrlen_t) GetProcAddress (ucrt, "mbrlen");

  if (real_mbrlen == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain address of mbrlen function\n");
    abort ();
  }

  InterlockedExchangePointer ((PVOID volatile *) &__mbrlen, (PVOID) real_mbrlen);
  FreeLibrary (ucrt);

  return __mbrlen (mbs, count, state);
}

static size_t mbrtowc_init (
  wchar_t *__restrict__ wc,
  const char *__restrict__ mbs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  HANDLE ucrt = LoadLibraryW (L"ucrtbase.dll");

  if (ucrt == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain handle to ucrtbase.dll\n");
    abort ();
  }

  __mbrtowc_t real_mbrtowc = (__mbrtowc_t) GetProcAddress (ucrt, "mbrtowc");

  if (real_mbrtowc == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain address of mbrtowc function\n");
    abort ();
  }

  InterlockedExchangePointer ((PVOID volatile *) &__mbrtowc, (PVOID) real_mbrtowc);
  FreeLibrary (ucrt);

  return __mbrtowc (wc, mbs, count, state);
}

static size_t mbsrtowcs_init (
  wchar_t *__restrict__ wcs,
  const char **__restrict__ mbs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  HANDLE ucrt = LoadLibraryW (L"ucrtbase.dll");

  if (ucrt == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain handle to ucrtbase.dll\n");
    abort ();
  }

  __mbsrtowcs_t real_mbsrtowcs = (__mbsrtowcs_t) GetProcAddress (ucrt, "mbsrtowcs");

  if (real_mbsrtowcs == NULL) {
    fwprintf (stderr, L"Runtime error: failed to obtain address of mbsrtowcs function\n");
    abort ();
  }

  InterlockedExchangePointer ((PVOID volatile *) &__mbsrtowcs, (PVOID) real_mbsrtowcs);
  FreeLibrary (ucrt);

  return __mbsrtowcs (wcs, mbs, count, state);
}

size_t __cdecl mbrlen (
  const char *__restrict__ mbs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  if (MB_CUR_MAX > 2) {
    return __mbrlen (mbs, count, state);
  }
  return __mingw_mbrlen (mbs, count, state);
}

size_t __cdecl mbrtowc (
  wchar_t *__restrict__ wc,
  const char *__restrict__ mbs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  if (MB_CUR_MAX > 2) {
    return __mbrtowc (wc, mbs, count, state);
  }
  return __mingw_mbrtowc (wc, mbs, count, state);
}

size_t __cdecl mbsrtowcs (
  wchar_t *__restrict__ wc,
  const char **__restrict__ mbs,
  size_t count,
  mbstate_t *__restrict__ state
) {
  if (MB_CUR_MAX > 2) {
    return __mbsrtowcs (wc, mbs, count, state);
  }
  return __mingw_mbsrtowcs (wc, mbs, count, state);
}
