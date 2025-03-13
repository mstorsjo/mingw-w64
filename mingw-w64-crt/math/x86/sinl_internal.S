/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#include <_mingw_mac.h>

	.file	"sinl_internal.S"
	.text
#ifdef __x86_64__
	.align 8
#else
	.align 4
#endif
.globl __MINGW_USYMBOL(__sinl_internal)
	.def	__MINGW_USYMBOL(__sinl_internal);	.scl	2;	.type	32;	.endef
__MINGW_USYMBOL(__sinl_internal):
#ifdef __x86_64__
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
	sub	$16, %rsp
	movsd	%xmm0, (%rsp)
	fldl	(%rsp)
#else
	fldt	(%rdx)
#endif
	fsin
	fnstsw	%ax
	testl	$0x400,%eax
	jnz	1f
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
1:	fldpi
	fadd	%st(0)
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	testl	$0x400,%eax
	jnz	2b
	fstp	%st(1)
	fsin
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
#if __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
	fldl	4(%esp)
#else
	fldt	4(%esp)
#endif
	fsin
	fnstsw	%ax
	testl	$0x400,%eax
	jnz	1f
	ret
1:	fldpi
	fadd	%st(0)
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	testl	$0x400,%eax
	jnz	2b
	fstp	%st(1)
	fsin
	ret
#endif
