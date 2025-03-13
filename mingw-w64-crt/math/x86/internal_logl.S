/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#include <_mingw_mac.h>

	.file	"internal_logl.S"
	.text
#ifdef __x86_64__
	.align 8
#else
	.align 4
#endif
one:	.double 1.0
	/* It is not important that this constant is precise.  It is only
	   a value which is known to be on the safe side for using the
	   fyl2xp1 instruction.  */
limit:	.double 0.29

.globl __MINGW_USYMBOL(__logl_internal)
	.def	__MINGW_USYMBOL(__logl_internal);	.scl	2;	.type	32;	.endef
__MINGW_USYMBOL(__logl_internal):
#ifdef __x86_64__
	fldln2			// log(2)
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
	sub	$16, %rsp
	movsd	%xmm0, (%rsp)
	fldl	(%rsp)		// x : log(2)
#else
	fldt	(%rdx)		// x : log(2)
#endif
	fld	%st		// x : x : log(2)
	fsubl	one(%rip)	// x-1 : x : log(2)
	fld	%st		// x-1 : x-1 : x : log(2)
	fabs			// |x-1| : x-1 : x : log(2)
	fcompl	limit(%rip)	// x-1 : x : log(2)
	fnstsw			// x-1 : x : log(2)
	andb	$0x45, %ah
	jz	2f
	fstp	%st(1)		// x-1 : log(2)
	fyl2xp1			// log(x)
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
	fstpl	(%rsp)
	movsd	(%rsp), %xmm0
	add	$16, %rsp
#else
	movq	%rcx,%rax
	movq	$0,8(%rcx)
	fstpt	(%rcx)
#endif
	ret

2:	fstp	%st(0)		// x : log(2)
	fyl2x			// log(x)
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
	fstpl	(%rsp)
	movsd	(%rsp), %xmm0
	add	$16, %rsp
#else
	movq	%rcx,%rax
	movq	$0,8(%rcx)
	fstpt	(%rcx)
#endif
	ret
#else
	fldln2			// log(2)
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
	fldl	4(%esp)		// x : log(2)
#else
	fldt	4(%esp)		// x : log(2)
#endif
	fld	%st		// x : x : log(2)
	fsubl	one		// x-1 : x : log(2)
	fld	%st		// x-1 : x-1 : x : log(2)
	fabs			// |x-1| : x-1 : x : log(2)
	fcompl	limit		// x-1 : x : log(2)
	fnstsw			// x-1 : x : log(2)
	andb	$0x45, %ah
	jz	2f
	fstp	%st(1)		// x-1 : log(2)
	fyl2xp1			// log(x)
	ret

2:	fstp	%st(0)		// x : log(2)
	fyl2x			// log(x)
	ret
#endif
