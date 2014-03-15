	.cpu cortex-m0
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 4
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.code	16
	.file	"ip_checksum.c"
	.text
	.align	1
	.global	ip_checksum
	.code	16
	.thumb_func
	.type	ip_checksum, %function
ip_checksum:
	push	{r4, r5, r6, lr}
	add	r4, r1, r2
	sub	r6, r4, #7
	mov	r5, #0
	b	.L2
.L3:
@ 81 "ip_checksum.c" 1
	ldm	r1!, {r2,r3}
	add	r0, r2
	adc	r0, r3
	adc	r0, r5
@ 0 "" 2
	.code	16
.L2:
	cmp	r1, r6
	bcc	.L3
	lsr	r3, r0, #16
	uxth	r0, r0
	add	r0, r0, r3
	sub	r3, r4, #1
	b	.L4
.L5:
	ldrh	r2, [r1]
	add	r1, r1, #2
	add	r0, r0, r2
.L4:
	cmp	r1, r3
	bcc	.L5
	cmp	r1, r4
	bcs	.L6
	ldrb	r3, [r1]
	add	r0, r3, r0
.L6:
	lsr	r3, r0, #16
	uxth	r0, r0
	add	r0, r0, r3
	lsr	r3, r0, #16
	uxth	r0, r0
	add	r0, r0, r3
	mvn	r0, r0
	uxth	r0, r0
	@ sp needed for prologue
	pop	{r4, r5, r6, pc}
	.size	ip_checksum, .-ip_checksum
	.ident	"GCC: (GNU) 4.7.1"
