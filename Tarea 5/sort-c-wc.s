	.file	"sort-c-wc.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	palabras
	.type	palabras, @function
palabras:
	mv	a5,a0
	li	a0,0
	li	a3,32
	j	.L4
.L3:
	addi	a5,a5,1
	lbu	a4,0(a5)
	beq	a4,a3,.L3
	bne	a4,zero,.L15
.L4:
	lbu	a4,0(a5)
	beq	a4,zero,.L1
	beq	a4,a3,.L3
	addi	a0,a0,1
.L7:
	beq	a4,zero,.L4
	addi	a5,a5,1
	lbu	a4,0(a5)
	bne	a4,a3,.L7
	j	.L4
.L15:
	addi	a0,a0,1
	beq	a4,a3,.L4
	j	.L7
.L1:
	ret
	.size	palabras, .-palabras
	.ident	"GCC: () 11.1.0"
