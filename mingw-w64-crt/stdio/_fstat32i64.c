/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#define __CRT__NO_INLINE
#include <sys/stat.h>

int __cdecl _fstat32i64(int _FileDes,struct _stat32i64 *_Stat)
{
  struct _stat64 st;
  int ret=_fstat64(_FileDes,&st);
  if (ret != 0)
    return ret;
  _Stat->st_dev=st.st_dev;
  _Stat->st_ino=st.st_ino;
  _Stat->st_mode=st.st_mode;
  _Stat->st_nlink=st.st_nlink;
  _Stat->st_uid=st.st_uid;
  _Stat->st_gid=st.st_gid;
  _Stat->st_rdev=st.st_rdev;
  _Stat->st_size=st.st_size;
  _Stat->st_atime=(__time32_t) st.st_atime; /* truncate 64-bit st_atime to 32-bit */
  _Stat->st_mtime=(__time32_t) st.st_mtime; /* truncate 64-bit st_mtime to 32-bit */
  _Stat->st_ctime=(__time32_t) st.st_ctime; /* truncate 64-bit st_ctime to 32-bit */
  return 0;
}
int (__cdecl *__MINGW_IMP_SYMBOL(_fstat32i64))(int, struct _stat32i64 *) = _fstat32i64;

#undef _fstati64
int __attribute__ ((alias ("_fstat32i64"))) __cdecl _fstati64(int, struct _stat32i64 *);
extern int __attribute__ ((alias (__MINGW64_STRINGIFY(__MINGW_IMP_SYMBOL(_fstat32i64))))) (__cdecl *__MINGW_IMP_SYMBOL(_fstati64))(int, struct _stat32i64 *);
