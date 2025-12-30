/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <locale.h>

/* By default the ANSI (ACP) is used, fallack to default ANSI when function AreFileApisANSI() is not available */
static BOOL WINAPI fallbackAreFileApisANSI(VOID) { return TRUE; }

unsigned int __cdecl __mingw_filename_cp(void)
{
  if (___lc_codepage_func() == CP_UTF8)
    return CP_UTF8;

  /* Function AreFileApisANSI() is not available in older Windows versions, so resolve it at runtime */
  static BOOL (WINAPI *myAreFileApisANSI)(VOID) = NULL;
  if (!myAreFileApisANSI) {
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    FARPROC farproc = kernel32 ? GetProcAddress(kernel32, "AreFileApisANSI") : NULL;
    (void)InterlockedExchangePointer((PVOID*)&myAreFileApisANSI, farproc ?: fallbackAreFileApisANSI);
  }
  return myAreFileApisANSI() ? CP_ACP : CP_OEMCP;
}
