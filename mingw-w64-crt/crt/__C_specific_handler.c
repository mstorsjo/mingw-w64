/*
    Copyright (c) 2020 mingw-w64 project

    Contributing authors: Martin Storsjo

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <excpt.h>

#if defined(__x86_64__) || defined(__arm__) || defined(__aarch64__)
EXCEPTION_DISPOSITION __cdecl
__C_specific_handler(struct _EXCEPTION_RECORD *_ExceptionRecord,
                     void *_EstablisherFrame,
                     struct _CONTEXT *_ContextRecord,
                     struct _DISPATCHER_CONTEXT *_DispatcherContext)
{
  (void)_ExceptionRecord;
  (void)_EstablisherFrame;
  (void)_ContextRecord;
  (void)_DispatcherContext;
  // TODO A more comprehensive implementation. Normally this is only used
  // by the toplevel SEH handler for uncaught exceptions, for calling
  // signal handlers. If signal handling isn't used, this no-op implementation
  // should be ok. Wine does contain a supposedly correct implementation of
  // this for x86_64 at least.
  return ExceptionContinueSearch;
}

EXCEPTION_DISPOSITION
(__cdecl *__MINGW_IMP_SYMBOL(__C_specific_handler))(
    struct _EXCEPTION_RECORD *_ExceptionRecord,
    void *_EstablisherFrame,
    struct _CONTEXT *_ContextRecord,
    struct _DISPATCHER_CONTEXT *_DispatcherContext) = __C_specific_handler;
#endif
