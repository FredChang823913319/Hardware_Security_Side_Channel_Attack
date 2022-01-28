	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$128, %rsp
	leaq	L_.str(%rip), %rdi
	leaq	L_.str.1(%rip), %rsi
	movl	$0, -4(%rbp)
	callq	_fopen
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	LBB0_2
## %bb.1:
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -4(%rbp)
	movl	%eax, -80(%rbp)         ## 4-byte Spill
	jmp	LBB0_28
LBB0_2:
	movl	$0, -64(%rbp)
LBB0_3:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -64(%rbp)
	jge	LBB0_6
## %bb.4:                               ##   in Loop: Header=BB0_3 Depth=1
	movq	_sender@GOTPCREL(%rip), %rax
	movl	-64(%rbp), %ecx
	movl	-64(%rbp), %edx
	shll	$4, %edx
	movslq	%edx, %rsi
	movl	%ecx, (%rax,%rsi,4)
## %bb.5:                               ##   in Loop: Header=BB0_3 Depth=1
	movl	-64(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -64(%rbp)
	jmp	LBB0_3
LBB0_6:
	movl	$0, -68(%rbp)
LBB0_7:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$90, -68(%rbp)
	jge	LBB0_10
## %bb.8:                               ##   in Loop: Header=BB0_7 Depth=1
	leaq	L_.str.3(%rip), %rdi
	movq	_sender@GOTPCREL(%rip), %rax
	movl	-68(%rbp), %ecx
	shll	$4, %ecx
	movslq	%ecx, %rdx
	shlq	$2, %rdx
	addq	%rdx, %rax
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	movq	_sender@GOTPCREL(%rip), %rdx
	mfence
	movl	-68(%rbp), %ecx
	shll	$4, %ecx
	movslq	%ecx, %rsi
	shlq	$2, %rsi
	addq	%rsi, %rdx
	clflush	(%rdx)
	movl	%eax, -84(%rbp)         ## 4-byte Spill
## %bb.9:                               ##   in Loop: Header=BB0_7 Depth=1
	movl	-68(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -68(%rbp)
	jmp	LBB0_7
LBB0_10:
	movl	$0, -72(%rbp)
LBB0_11:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -72(%rbp)
	jge	LBB0_23
## %bb.12:                              ##   in Loop: Header=BB0_11 Depth=1
	leaq	L_.str.4(%rip), %rdi
	movq	_sender@GOTPCREL(%rip), %rax
	mfence
	lfence
	movq	%rax, -96(%rbp)         ## 8-byte Spill
	rdtsc
	shlq	$32, %rdx
	orq	%rdx, %rax
	movq	%rax, -24(%rbp)
	lfence
	movl	-72(%rbp), %ecx
	shll	$4, %ecx
	movslq	%ecx, %rax
	movq	-96(%rbp), %rdx         ## 8-byte Reload
	movl	(%rdx,%rax,4), %ecx
	movl	%ecx, -52(%rbp)
	lfence
	rdtsc
	shlq	$32, %rdx
	orq	%rdx, %rax
	movq	%rax, -32(%rbp)
	lfence
	movq	-32(%rbp), %rax
	subq	-24(%rbp), %rax
	movl	%eax, %ecx
	movl	%ecx, -56(%rbp)
	mfence
	lfence
	rdtsc
	shlq	$32, %rdx
	orq	%rdx, %rax
	movq	%rax, -40(%rbp)
	lfence
	lfence
	rdtsc
	shlq	$32, %rdx
	orq	%rdx, %rax
	movq	%rax, -48(%rbp)
	lfence
	movq	-48(%rbp), %rax
	subq	-40(%rbp), %rax
	movl	%eax, %ecx
	movl	%ecx, -60(%rbp)
	movl	-56(%rbp), %esi
	movl	-60(%rbp), %edx
	movl	-72(%rbp), %ecx
	movb	$0, %al
	callq	_printf
	movl	-56(%rbp), %ecx
	cmpl	-60(%rbp), %ecx
	movl	%eax, -100(%rbp)        ## 4-byte Spill
	jbe	LBB0_14
## %bb.13:                              ##   in Loop: Header=BB0_11 Depth=1
	movl	-56(%rbp), %eax
	subl	-60(%rbp), %eax
	movl	%eax, -56(%rbp)
	jmp	LBB0_15
LBB0_14:                                ##   in Loop: Header=BB0_11 Depth=1
	movl	$0, -56(%rbp)
LBB0_15:                                ##   in Loop: Header=BB0_11 Depth=1
	movq	_time@GOTPCREL(%rip), %rax
	movl	-72(%rbp), %ecx
	movslq	-72(%rbp), %rdx
	shlq	$4, %rdx
	movq	%rax, %rsi
	addq	%rdx, %rsi
	movl	%ecx, (%rsi)
	movl	-56(%rbp), %ecx
	movslq	-72(%rbp), %rdx
	shlq	$4, %rdx
	movq	%rax, %rsi
	addq	%rdx, %rsi
	movl	%ecx, 4(%rsi)
	movl	-60(%rbp), %ecx
	movslq	-72(%rbp), %rdx
	shlq	$4, %rdx
	addq	%rdx, %rax
	movl	%ecx, 8(%rax)
	cmpl	$60, -56(%rbp)
	jbe	LBB0_17
## %bb.16:                              ##   in Loop: Header=BB0_11 Depth=1
	movq	_cache@GOTPCREL(%rip), %rax
	movq	_receiver@GOTPCREL(%rip), %rcx
	movslq	-72(%rbp), %rdx
	movl	$1, (%rcx,%rdx,4)
	movslq	-72(%rbp), %rcx
	movb	$1, (%rax,%rcx)
	jmp	LBB0_18
LBB0_17:                                ##   in Loop: Header=BB0_11 Depth=1
	movq	_cache@GOTPCREL(%rip), %rax
	movq	_receiver@GOTPCREL(%rip), %rcx
	movslq	-72(%rbp), %rdx
	movl	$0, (%rcx,%rdx,4)
	movslq	-72(%rbp), %rcx
	movb	$0, (%rax,%rcx)
LBB0_18:                                ##   in Loop: Header=BB0_11 Depth=1
	movq	_cache@GOTPCREL(%rip), %rax
	movslq	-72(%rbp), %rcx
	testb	$1, (%rax,%rcx)
	je	LBB0_20
## %bb.19:                              ##   in Loop: Header=BB0_11 Depth=1
	leaq	L_.str.5(%rip), %rdi
	movq	_time@GOTPCREL(%rip), %rax
	movslq	-72(%rbp), %rcx
	shlq	$4, %rcx
	addq	%rcx, %rax
	movl	$1, 12(%rax)
	movb	$0, %al
	callq	_printf
	movl	%eax, -104(%rbp)        ## 4-byte Spill
	jmp	LBB0_21
LBB0_20:                                ##   in Loop: Header=BB0_11 Depth=1
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	_time@GOTPCREL(%rip), %rdi
	movslq	-72(%rbp), %rcx
	shlq	$4, %rcx
	addq	%rcx, %rdi
	movl	$0, 12(%rdi)
	movl	%eax, -108(%rbp)        ## 4-byte Spill
LBB0_21:                                ##   in Loop: Header=BB0_11 Depth=1
	jmp	LBB0_22
LBB0_22:                                ##   in Loop: Header=BB0_11 Depth=1
	movl	-72(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -72(%rbp)
	jmp	LBB0_11
LBB0_23:
	movl	$0, -76(%rbp)
LBB0_24:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$100, -76(%rbp)
	jge	LBB0_27
## %bb.25:                              ##   in Loop: Header=BB0_24 Depth=1
	leaq	L_.str.7(%rip), %rsi
	movq	_time@GOTPCREL(%rip), %rax
	movq	-16(%rbp), %rdi
	movslq	-76(%rbp), %rcx
	shlq	$4, %rcx
	movq	%rax, %rdx
	addq	%rcx, %rdx
	movl	(%rdx), %edx
	movslq	-76(%rbp), %rcx
	shlq	$4, %rcx
	movq	%rax, %r8
	addq	%rcx, %r8
	movl	4(%r8), %ecx
	movslq	-76(%rbp), %r8
	shlq	$4, %r8
	movq	%rax, %r9
	addq	%r8, %r9
	movl	8(%r9), %r8d
	movslq	-76(%rbp), %r9
	shlq	$4, %r9
	addq	%r9, %rax
	movl	12(%rax), %r9d
	movb	$0, %al
	callq	_fprintf
	movl	%eax, -112(%rbp)        ## 4-byte Spill
## %bb.26:                              ##   in Loop: Header=BB0_24 Depth=1
	movl	-76(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -76(%rbp)
	jmp	LBB0_24
LBB0_27:
	movq	-16(%rbp), %rdi
	callq	_fclose
	movl	%eax, -116(%rbp)        ## 4-byte Spill
LBB0_28:
	movl	-4(%rbp), %eax
	addq	$128, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"sample1.txt"

L_.str.1:                               ## @.str.1
	.asciz	"w"

L_.str.2:                               ## @.str.2
	.asciz	"Could not open file"

	.comm	_sender,6400,4          ## @sender
L_.str.3:                               ## @.str.3
	.asciz	"address = %p \n"

L_.str.4:                               ## @.str.4
	.asciz	"before: %u,%u, %d\n"

	.comm	_time,1600,4            ## @time
	.comm	_receiver,400,4         ## @receiver
	.comm	_cache,100,4            ## @cache
L_.str.5:                               ## @.str.5
	.asciz	"1\n"

L_.str.6:                               ## @.str.6
	.asciz	"0\n"

L_.str.7:                               ## @.str.7
	.asciz	"%u, %u, %u, %u\n"


.subsections_via_symbols
