/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdio.h>
#include <errno.h>
#include <io.h>
#include <fcntl.h>
#include <internal.h>
#include <windows.h>
#include <winternl.h>
#include <ntstatus.h>

static NTSTATUS NTAPI MyNtQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass)
{
  static NTSTATUS (NTAPI *NtQueryInformationFilePtr)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG, FILE_INFORMATION_CLASS);
  static volatile LONG init = 0;

  if (!init) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    FARPROC func = ntdll ? GetProcAddress(ntdll, "NtQueryInformationFile") : NULL;
    (void)InterlockedExchangePointer((PVOID volatile *)&NtQueryInformationFilePtr, func);
    (void)InterlockedExchange(&init, 1);
  }

  if (!NtQueryInformationFilePtr)
    return STATUS_NOT_IMPLEMENTED;
  else
    return NtQueryInformationFilePtr(FileHandle, IoStatusBlock, FileInformation, Length, FileInformationClass);
}
#define NtQueryInformationFile MyNtQueryInformationFile

static NTSTATUS NTAPI MyNtSetInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass)
{
  static NTSTATUS (NTAPI *NtSetInformationFilePtr)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG, FILE_INFORMATION_CLASS);
  static volatile LONG init = 0;

  if (!init) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    FARPROC func = ntdll ? GetProcAddress(ntdll, "NtSetInformationFile") : NULL;
    (void)InterlockedExchangePointer((PVOID volatile *)&NtSetInformationFilePtr, func);
    (void)InterlockedExchange(&init, 1);
  }

  if (!NtSetInformationFilePtr)
    return STATUS_NOT_IMPLEMENTED;
  else
    return NtSetInformationFilePtr(FileHandle, IoStatusBlock, FileInformation, Length, FileInformationClass);
}
#define NtSetInformationFile MyNtSetInformationFile


_CRTIMP FILE *__cdecl _freopen(const char *restrict filename, const char *restrict mode, FILE *restrict file);

FILE *__cdecl freopen(const char *restrict filename, const char *restrict mode, FILE *restrict file)
{
  int new_stream_flags;
  int new_mode_flags;
  int new_mode;
  int change_iocommit;
  int fd;
  HANDLE handle;
  FILE_MODE_INFORMATION file_mode_information;
  IO_STATUS_BLOCK io_status_block;
  NTSTATUS status;

  /* This mingw-w64 function handles only case when the filename is NULL and
   * both mode and file are specified. Forward all other cases to the original
   * msvcrt freopen function.
   */
  if (!(!filename && mode && file))
    return _freopen(filename, mode, file);


  /* As a first step parse freopen mode and reject any invalid combinations
   * in the same way and same behavior as the original msvcrt freopen function.
   */

  while (*mode == ' ')
    mode++;

  new_stream_flags = _commode; /* default stream flags are in global variable _commode */
  new_mode_flags = 0;
  change_iocommit = 0;

  if (*mode == 'r')
    new_stream_flags |= _IOREAD;
  else if (*mode == 'w' || *mode == 'a') /* FIXME: changing between 'w' and 'a' is ignored and does not trigger any error */
    new_stream_flags |= _IOWRT;
  else
    goto err_inval;

  while (*++mode) {
    if (*mode == ' ')
      continue;

    if (*mode == '+') {
      if (new_stream_flags & _IORW)
        goto err_inval;
      new_stream_flags |= _IORW;
      new_stream_flags &= ~(_IOREAD | _IOWRT);
    } else if (*mode == 'b') {
      if (new_mode_flags & (_O_TEXT | _O_BINARY))
        goto err_inval;
      new_mode_flags |= _O_BINARY;
    } else if (*mode == 't') {
      if (new_mode_flags & (_O_TEXT | _O_BINARY))
        goto err_inval;
      new_mode_flags |= _O_TEXT;
    } else if (*mode == 'c') {
      if (change_iocommit)
        goto err_inval;
      new_stream_flags |= _IOCOMMIT;
      change_iocommit = 1;
    } else if (*mode == 'n') {
      if (change_iocommit)
        goto err_inval;
      new_stream_flags &= ~_IOCOMMIT;
      change_iocommit = 1;
    } else if (*mode == 'S') {
      if (new_mode_flags & (_O_SEQUENTIAL | _O_RANDOM))
        goto err_inval;
      new_mode_flags |= _O_SEQUENTIAL;
    } else if (*mode == 'R') {
      if (new_mode_flags & (_O_SEQUENTIAL | _O_RANDOM))
        goto err_inval;
      new_mode_flags |= _O_RANDOM;
    } else if (*mode == 'T') {
      if (new_mode_flags & _O_SHORT_LIVED)
        goto err_inval;
      new_mode_flags |= _O_SHORT_LIVED;
    } else if (*mode == 'D') {
      if (new_mode_flags & _O_TEMPORARY)
        goto err_inval;
      new_mode_flags |= _O_TEMPORARY;
    } else if (*mode == 'N') {
      /* msvcrt does not check for duplicate N characters */
      new_mode_flags |= _O_NOINHERIT;
    } else if (*mode == ',') {
      while (*mode == ' ')
        mode++;
      if (strncmp(mode, "ccs", 3) != 0)
        goto err_inval;
      mode += 3;
      while (*mode == ' ')
        mode++;
      if (*mode != '=')
        goto err_inval;
      while (*mode == ' ')
        mode++;
      if (stricmp(mode, "UTF-8") == 0)
        new_mode_flags |= _O_U8TEXT;
      else if (stricmp(mode, "UTF-16LE") == 0)
        new_mode_flags |= _O_U16TEXT;
      else if (stricmp(mode, "UNICODE") == 0)
        new_mode_flags |= _O_WTEXT;
      else
        goto err_inval;
      /* after ",css=" there is no other mode specifier, stricmp checks for this */
    } else {
      goto err_inval;
    }
  }

  /* If mode is not specified then the default one from the global variable _fmode is used */
  if (!(new_mode_flags & (_O_BINARY | _O_TEXT | _O_U8TEXT | _O_U16TEXT | _O_WTEXT)))
    new_mode_flags |= _fmode & (_O_BINARY | _O_TEXT | _O_U8TEXT | _O_U16TEXT | _O_WTEXT);

  /* If mode is not specified neither in _fmode then the fallback value is always _O_TEXT */
  if (!(new_mode_flags & (_O_BINARY | _O_TEXT | _O_U8TEXT | _O_U16TEXT | _O_WTEXT)))
    new_mode_flags |= _O_TEXT;

  /* Changing of _IOREAD, _IOWRT and _IORW is not possible */
  if ((new_stream_flags & (_IOREAD | _IOWRT | _IORW)) != (file->_flags & (_IOREAD | _IOWRT | _IORW)))
    goto err_inval;


  /* As a second step take CRT file descriptor and WINAPI handle */

  fd = fileno(file);
  if (fd < 0)
    return NULL;

  handle = (HANDLE)_get_osfhandle(fd);
  if (handle == INVALID_HANDLE_VALUE)
    return NULL;


  /* As a third step before changing any FILE*, fd or HANDLE characteristics, flush all buffers */
  /* This ensures that data in buffer are processed by existing settings */
  fflush(file);


  /* As a fourth step process _O_SEQUENTIAL, _O_TEMPORARY, _O_NOINHERIT, _O_SHORT_LIVED and _O_RANDOM flags */

  /* CRT _O_SEQUENTIAL flag is mapped to WINAPI FILE_FLAG_SEQUENTIAL_SCAN flag
   * which is mapped to NT FILE_SEQUENTIAL_ONLY flag. WINAPI does not provide
   * API to query or change this flag on already opened file handle. NT API
   * provides functions NtQueryInformationFile() and NtSetInformationFile()
   * with class FileModeInformation which allows that. WINAPI functions
   * GetFileInformationByHandleEx() and SetFileInformationByHandle() do not
   * support FileModeInfo level yet.
   * Our NtQueryInformationFile wrapper returns STATUS_NOT_IMPLEMENTED when
   * the NtQueryInformationFile function is not supported.
   * For console handle: wine returns STATUS_OBJECT_TYPE_MISMATCH,
   * Windows XP returns STATUS_INVALID_HANDLE and Windows 10 returns
   * STATUS_SUCCESS.
   * Treat STATUS_NOT_IMPLEMENTED, STATUS_OBJECT_TYPE_MISMATCH and
   * STATUS_INVALID_HANDLE codes as if the FILE_SEQUENTIAL_ONLY was not set
   * and setting it is not supported.
   */
  status = NtQueryInformationFile(handle, &io_status_block, &file_mode_information, sizeof(file_mode_information), FileModeInformation);
  if (status == STATUS_NOT_IMPLEMENTED || status == STATUS_OBJECT_TYPE_MISMATCH || status == STATUS_INVALID_HANDLE) {
    if (new_mode_flags & _O_SEQUENTIAL)
      goto err_inval;
  } else if (status == STATUS_SUCCESS) {
    if (!!(new_mode_flags & _O_SEQUENTIAL) != !!(file_mode_information.Mode & FILE_SEQUENTIAL_ONLY)) {
      if (new_mode_flags & _O_SEQUENTIAL)
        file_mode_information.Mode |= FILE_SEQUENTIAL_ONLY;
      else
        file_mode_information.Mode &= ~FILE_SEQUENTIAL_ONLY;
      status = NtSetInformationFile(handle, &io_status_block, &file_mode_information, sizeof(file_mode_information), FileModeInformation);
      if (status != STATUS_SUCCESS)
        goto err_inval;
    }
  } else {
    goto err_inval;
  }

  /* CRT _O_TEMPORARY flag is mapped to WINAPI FILE_FLAG_DELETE_ON_CLOSE flag
   * which is mapped to NT FILE_DELETE_ON_CLOSE flag. There is no API which
   * allows to query that flag. Function GetFileInformationByHandleEx() does
   * not support levels FileDispositionInfo and FileDispositionInfoEx. And
   * function NtQueryInformationFile() does not support classes
   * FileDispositionInformation and FileDispositionInformationEx.
   * Setting or clearing this flag on already opened file handle is possible
   * only on filesystem which supports FileDispositionInformationEx
   * FILE_DISPOSITION_ON_CLOSE flag (e.g. on NTFS since Windows 10 1607)
   * via either WINAPI SetFileInformationByHandle() function with level
   * FileDispositionInfoEx or via NT NtSetInformationFile() function with class
   * FileDispositionInformationEx, together with specifying
   * FILE_DISPOSITION_ON_CLOSE flag. According to MS-FSCC documentation,
   * setting of this flag will fail with STATUS_NOT_SUPPORTED if the
   * NT FILE_DELETE_ON_CLOSE flag was not specified during opening the file.
   * So there is no reliable way to query, clear or set FILE_DELETE_ON_CLOSE
   * flag. Therefore ignore the CRT _O_TEMPORARY flag.
   */

  /* CRT _O_NOINHERIT flag is mapped to CRT ioinfo osfile flag FNOINHERIT and
   * also to WINAPI SecurityAttributes bInheritHandle. WINAPI inheritance can
   * be queried or changed by GetHandleInformation() and SetHandleInformation()
   * functions with HANDLE_FLAG_INHERIT mask.
   * Changing of CRT ioinfo osfile flag FNOINHERIT is not possible without
   * touching CRT internals. So ignore the CRT _O_NOINHERIT flag.
   */


  /* CRT _O_SHORT_LIVED flag is mapped to WINAPI FILE_ATTRIBUTE_TEMPORARY flag
   * which applies only when creating a new file. msvcrt and UCRT accepts the
   * _O_SHORT_LIVED also when opening an existing file and in this case the
   * flag is ignored. freopen with NULL filename re-opens an existing file,
   * so always ignore the CRT _O_SHORT_LIVED flag.
   */

  /* CRT _O_RANDOM flag is mapped to WINAPI FILE_FLAG_RANDOM_ACCESS flag which
   * is mapped to NT FILE_RANDOM_ACCESS flag. There is no WINAPI or NT function
   * which allows to query, clear or set this flag. So ignore any attempt to set
   * or to clear this CRT flag without throwing any error.
   */


  /* As a fifth step process _O_BINARY, _O_TEXT, _O_WTEXT, _O_U16TEXT, _O_U8TEXT flags */

  /* Choose the correct new mode. If more mode flags are specified then msvcrt chooses the first in this order. */
  if (new_mode_flags & _O_BINARY)
    new_mode = _O_BINARY;
  else if (new_mode_flags & _O_TEXT)
    new_mode = _O_TEXT;
  else if (new_mode_flags & _O_WTEXT)
    new_mode = _O_WTEXT;
  else if (new_mode_flags & _O_U16TEXT)
    new_mode = _O_U16TEXT;
  else if (new_mode_flags & _O_U8TEXT)
    new_mode = _O_U8TEXT;
  else
    goto err_inval; /* should not happen */

  if (_setmode(fd, new_mode) < 0)
    return NULL;


  /* As a sixth step process _IOCOMMIT flag */

  /* CRT _IOCOMMIT flag is set only in the FILE* structure. So atomically set or clear it. */
  if (change_iocommit) {
    if (new_stream_flags & _IOCOMMIT)
      InterlockedOr((LONG volatile *)&file->_flags, _IOCOMMIT);
    else
      InterlockedAnd((LONG volatile *)&file->_flags, ~_IOCOMMIT);
  }


  /* All done */
  return file;

err_inval:
  errno = EINVAL;
  return NULL;
}
FILE * (__cdecl *__MINGW_IMP_SYMBOL(freopen))(const char *restrict, const char *restrict, FILE *restrict) = freopen;

FILE * __attribute__((alias("freopen"))) __cdecl freopen64(const char *restrict filename, const char *restrict mode, FILE *restrict file);
extern FILE * (__cdecl * __attribute__((alias (__MINGW64_STRINGIFY(__MINGW_IMP_SYMBOL(freopen))))) __MINGW_IMP_SYMBOL(freopen64))(const char *restrict, const char *restrict, FILE *restrict);
