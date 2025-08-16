/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

void __main (void);

__attribute__((used)) /* required for gcc -flto -Ofast */
void
__main (void)
{
  /* gcc during compilation of function named main() inserts at the beginning
   * of the execution a call to the function __main(). gcc expects that the
   * function __main() will execute all global C++ constructors which are
   * emitted by gcc itself. mingw-w64 runtime executes all gcc's global C++
   * constructors in mingw-w64 startup code (in crtdll.c and crtexe.c) before
   * executing function main. So the __main() function should do nothing as
   * when this function is called, all global C++ constructors were already
   * executed.
   */
}
