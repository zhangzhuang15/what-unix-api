	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 1
	.globl	_main                   ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16             ; =16
	.cfi_def_cfa_offset 16
	mov	w8, #0
	str	wzr, [sp, #12]
	mov	w9, #2
	str	w9, [sp, #8]
	mov	w9, #3
	str	w9, [sp, #4]
	ldr	w9, [sp, #8]
	ldr	w10, [sp, #4]
	add	w9, w9, w10
	str	w9, [sp, #8]
	mov	x0, x8
	add	sp, sp, #16             ; =16
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
