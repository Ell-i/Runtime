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
	.file	"udp.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.udp_input,"ax",%progbits
	.align	1
	.global	udp_input
	.code	16
	.thumb_func
	.type	udp_input, %function
udp_input:
.LFB37:
	.file 1 "udp.c"
	.loc 1 34 0
	.cfi_startproc
.LVL0:
	push	{r4, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 44 0
	ldrh	r3, [r0]
	.loc 1 43 0
	ldrh	r2, [r0, #2]
.LVL1:
.LBB16:
	.loc 1 48 0
	ldr	r1, .L6
.LBE16:
	.loc 1 44 0
	strh	r3, [r0, #2]
	.loc 1 45 0
	strh	r2, [r0]
.LVL2:
.LBB22:
	.loc 1 48 0
	ldr	r3, .L6+4
	b	.L2
.LVL3:
.L5:
	.loc 1 51 0
	ldrh	r4, [r3, #4]
	cmp	r4, r2
	bne	.L3
.LVL4:
.LBB17:
.LBB18:
.LBB19:
	.file 2 "../../libraries/CoAP/./util.h"
	.loc 2 38 0
	ldrh	r1, [r0, #4]
.LVL5:
.LBB20:
.LBB21:
	.file 3 "../../system/stm32/CMSIS/Include/core_cmInstr.h"
	.loc 3 428 0
@ 428 "../../system/stm32/CMSIS/Include/core_cmInstr.h" 1
	rev16 r1, r1
@ 0 "" 2
.LVL6:
	.code	16
.LBE21:
.LBE20:
.LBE19:
.LBE18:
	.loc 1 53 0
	sub	r1, r1, #8
.LVL7:
	.loc 1 54 0
	add	r0, r0, #8
.LVL8:
	uxth	r1, r1
.LVL9:
	ldr	r3, [r3]
.LVL10:
	blx	r3
.LVL11:
	.loc 1 55 0
	b	.L1
.LVL12:
.L3:
.LBE17:
	.loc 1 50 0
	add	r3, r3, #16
.LVL13:
.L2:
	.loc 1 48 0 discriminator 1
	cmp	r3, r1
	bcc	.L5
.LVL14:
.L1:
.LBE22:
	.loc 1 59 0
	@ sp needed for prologue
	pop	{r4, pc}
.L7:
	.align	2
.L6:
	.word	__udp_sockets_end
	.word	__udp_sockets
	.cfi_endproc
.LFE37:
	.size	udp_input, .-udp_input
	.section	.text.udp_output,"ax",%progbits
	.align	1
	.global	udp_output
	.code	16
	.thumb_func
	.type	udp_output, %function
udp_output:
.LFB39:
	.loc 1 120 0
	.cfi_startproc
.LVL15:
	push	{r4, r5, r6, lr}
.LCFI1:
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	.loc 1 123 0
	mov	r5, r1
	.loc 1 121 0
	mov	r4, r0
	.loc 1 123 0
	add	r5, r5, #8
	.loc 1 121 0
	sub	r4, r4, #8
.LVL16:
.LBB29:
.LBB30:
	.loc 2 37 0
	uxth	r3, r5
.LBB31:
.LBB32:
	.loc 3 428 0
@ 428 "../../system/stm32/CMSIS/Include/core_cmInstr.h" 1
	rev16 r3, r3
@ 0 "" 2
.LVL17:
	.code	16
.LBE32:
.LBE31:
.LBE30:
.LBE29:
.LBB33:
.LBB34:
	.loc 1 92 0
	mov	r6, #136
.LBE34:
.LBE33:
	.loc 1 125 0
	strh	r3, [r4, #4]
.LBB37:
.LBB35:
	.loc 1 91 0
	mov	r1, r0
.LVL18:
.LBE35:
.LBE37:
	.loc 1 126 0
	mov	r3, #0
.LVL19:
	strh	r3, [r4, #6]
.LVL20:
.LBB38:
.LBB36:
	.loc 1 92 0
	mov	r0, r5
.LVL21:
	lsl	r6, r6, #5
	.loc 1 91 0
	sub	r1, r1, #16
.LVL22:
	.loc 1 92 0
@ 92 "udp.c" 1
	ldm	r1!, {r2, r3}
	add	r0, r2
	adc	r0, r3
	adc	r0, r6
@ 0 "" 2
.LVL23:
	.loc 1 113 0
	.code	16
	mov	r2, r5
	mov	r1, r4
	bl	ip_checksum
.LVL24:
.LBE36:
.LBE38:
	.loc 1 135 0
	uxth	r1, r5
	.loc 1 131 0
	strh	r0, [r4, #6]
	.loc 1 135 0
	mov	r0, r4
	bl	ip_output
.LVL25:
	.loc 1 136 0
	@ sp needed for prologue
.LVL26:
.LVL27:
	pop	{r4, r5, r6, pc}
	.cfi_endproc
.LFE39:
	.size	udp_output, .-udp_output
	.section	.text.udp_echo,"ax",%progbits
	.align	1
	.global	udp_echo
	.code	16
	.thumb_func
	.type	udp_echo, %function
udp_echo:
.LFB40:
	.loc 1 138 0
	.cfi_startproc
.LVL28:
	push	{r3, lr}
.LCFI2:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 139 0
	bl	udp_output
.LVL29:
	.loc 1 140 0
	@ sp needed for prologue
	pop	{r3, pc}
	.cfi_endproc
.LFE40:
	.size	udp_echo, .-udp_echo
	.global	__udp_socket7
	.section	.socket.udp.7,"a",%progbits
	.align	4
	.type	__udp_socket7, %object
	.size	__udp_socket7, 16
__udp_socket7:
	.word	udp_echo
	.short	1792
	.space	10
	.text
.Letext0:
	.file 4 "/usr/local/Cellar/arm-eabi-yagarto/20120616/lib/gcc/arm-none-eabi/4.7.1/../../../../arm-none-eabi/sys-include/stdint.h"
	.file 5 "/usr/local/Cellar/arm-eabi-yagarto/20120616/lib/gcc/arm-none-eabi/4.7.1/include/stddef.h"
	.file 6 "../../libraries/CoAP/./udp.h"
	.file 7 "../../libraries/CoAP/./ip.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x62d
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x1
	.4byte	.LASF62
	.4byte	.LASF63
	.4byte	.Ldebug_ranges0+0x58
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF3
	.byte	0x4
	.byte	0x2a
	.4byte	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x4
	.byte	0x36
	.4byte	0x54
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.4byte	.LASF7
	.byte	0x4
	.byte	0x50
	.4byte	0x6d
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x5
	.byte	0xd5
	.4byte	0x89
	.uleb128 0x5
	.4byte	0x62
	.uleb128 0x5
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x6
	.byte	0x20
	.4byte	0x49
	.uleb128 0x6
	.ascii	"udp\000"
	.byte	0x8
	.byte	0x6
	.byte	0x24
	.4byte	0x10a
	.uleb128 0x7
	.4byte	.LASF15
	.byte	0x6
	.byte	0x25
	.4byte	0xac
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x6
	.byte	0x26
	.4byte	0xac
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x6
	.byte	0x27
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x7
	.4byte	.LASF18
	.byte	0x6
	.byte	0x28
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x7
	.4byte	.LASF19
	.byte	0x6
	.byte	0x29
	.4byte	0x10a
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x8
	.4byte	0x30
	.4byte	0x119
	.uleb128 0x9
	.4byte	0x90
	.byte	0
	.uleb128 0xa
	.4byte	.LASF20
	.byte	0x10
	.byte	0x6
	.byte	0x33
	.4byte	0x142
	.uleb128 0x7
	.4byte	.LASF21
	.byte	0x6
	.byte	0x34
	.4byte	0x159
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x7
	.4byte	.LASF22
	.byte	0x6
	.byte	0x35
	.4byte	0xa7
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.4byte	0x153
	.uleb128 0xc
	.4byte	0x153
	.uleb128 0xc
	.4byte	0x49
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x30
	.uleb128 0xd
	.byte	0x4
	.4byte	0x142
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x7
	.byte	0x23
	.4byte	0x62
	.uleb128 0xe
	.byte	0x4
	.byte	0x7
	.byte	0x28
	.4byte	0x189
	.uleb128 0xf
	.4byte	.LASF24
	.byte	0x7
	.byte	0x29
	.4byte	0x15f
	.uleb128 0xf
	.4byte	.LASF25
	.byte	0x7
	.byte	0x2a
	.4byte	0x189
	.byte	0
	.uleb128 0x8
	.4byte	0x30
	.4byte	0x199
	.uleb128 0x10
	.4byte	0x90
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.4byte	.LASF26
	.byte	0x4
	.byte	0x7
	.byte	0x27
	.4byte	0x1ae
	.uleb128 0x11
	.4byte	0x16a
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0xe
	.byte	0x2
	.byte	0x7
	.byte	0x35
	.4byte	0x1cd
	.uleb128 0xf
	.4byte	.LASF27
	.byte	0x7
	.byte	0x36
	.4byte	0x49
	.uleb128 0xf
	.4byte	.LASF28
	.byte	0x7
	.byte	0x37
	.4byte	0x1cd
	.byte	0
	.uleb128 0x8
	.4byte	0x30
	.4byte	0x1dd
	.uleb128 0x10
	.4byte	0x90
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.ascii	"ip\000"
	.byte	0x14
	.byte	0x7
	.byte	0x30
	.4byte	0x26f
	.uleb128 0x7
	.4byte	.LASF29
	.byte	0x7
	.byte	0x31
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x7
	.4byte	.LASF30
	.byte	0x7
	.byte	0x32
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x7
	.4byte	.LASF31
	.byte	0x7
	.byte	0x33
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x7
	.4byte	.LASF32
	.byte	0x7
	.byte	0x34
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x11
	.4byte	0x1ae
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x7
	.4byte	.LASF33
	.byte	0x7
	.byte	0x39
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x7
	.4byte	.LASF34
	.byte	0x7
	.byte	0x3a
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x7
	.4byte	.LASF35
	.byte	0x7
	.byte	0x3b
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x7
	.4byte	.LASF36
	.byte	0x7
	.byte	0x3c
	.4byte	0x199
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x7
	.4byte	.LASF37
	.byte	0x7
	.byte	0x3d
	.4byte	0x199
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0x12
	.4byte	.LASF38
	.byte	0x3
	.2byte	0x1a8
	.byte	0x1
	.4byte	0x62
	.byte	0x3
	.4byte	0x29a
	.uleb128 0x13
	.4byte	.LASF40
	.byte	0x3
	.2byte	0x1a8
	.4byte	0x62
	.uleb128 0x14
	.4byte	.LASF46
	.byte	0x3
	.2byte	0x1aa
	.4byte	0x62
	.byte	0
	.uleb128 0x15
	.4byte	.LASF39
	.byte	0x2
	.byte	0x26
	.byte	0x1
	.4byte	0x82
	.byte	0x3
	.4byte	0x2b5
	.uleb128 0x16
	.ascii	"s\000"
	.byte	0x2
	.byte	0x26
	.4byte	0x49
	.byte	0
	.uleb128 0x15
	.4byte	.LASF41
	.byte	0x2
	.byte	0x25
	.byte	0x1
	.4byte	0x82
	.byte	0x3
	.4byte	0x2d0
	.uleb128 0x16
	.ascii	"s\000"
	.byte	0x2
	.byte	0x25
	.4byte	0x49
	.byte	0
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF50
	.byte	0x1
	.byte	0x22
	.byte	0x1
	.4byte	.LFB37
	.4byte	.LFE37
	.4byte	.LLST0
	.byte	0x1
	.4byte	0x38f
	.uleb128 0x18
	.4byte	.LASF52
	.byte	0x1
	.byte	0x22
	.4byte	0x38f
	.4byte	.LLST1
	.uleb128 0x19
	.4byte	.LASF42
	.byte	0x1
	.byte	0x2b
	.4byte	0x49
	.4byte	.LLST2
	.uleb128 0x1a
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x19
	.4byte	.LASF43
	.byte	0x1
	.byte	0x30
	.4byte	0x39a
	.4byte	.LLST3
	.uleb128 0x1b
	.4byte	.LBB17
	.4byte	.LBE17
	.uleb128 0x19
	.4byte	.LASF44
	.byte	0x1
	.byte	0x35
	.4byte	0xa7
	.4byte	.LLST4
	.uleb128 0x1c
	.4byte	0x29a
	.4byte	.LBB18
	.4byte	.LBE18
	.byte	0x1
	.byte	0x35
	.4byte	0x37d
	.uleb128 0x1d
	.4byte	0x2ab
	.4byte	.LLST5
	.uleb128 0x1e
	.4byte	0x26f
	.4byte	.LBB20
	.4byte	.LBE20
	.byte	0x2
	.byte	0x26
	.uleb128 0x1d
	.4byte	0x281
	.4byte	.LLST6
	.uleb128 0x1b
	.4byte	.LBB21
	.4byte	.LBE21
	.uleb128 0x1f
	.4byte	0x28d
	.4byte	.LLST7
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x20
	.4byte	.LVL11
	.uleb128 0x21
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	0x394
	.uleb128 0xd
	.byte	0x4
	.4byte	0xb7
	.uleb128 0xd
	.byte	0x4
	.4byte	0x3a0
	.uleb128 0x5
	.4byte	0x119
	.uleb128 0x15
	.4byte	.LASF45
	.byte	0x1
	.byte	0x46
	.byte	0x1
	.4byte	0x49
	.byte	0x3
	.4byte	0x3f8
	.uleb128 0x16
	.ascii	"ip\000"
	.byte	0x1
	.byte	0x47
	.4byte	0x3f8
	.uleb128 0x16
	.ascii	"udp\000"
	.byte	0x1
	.byte	0x47
	.4byte	0x408
	.uleb128 0x16
	.ascii	"len\000"
	.byte	0x1
	.byte	0x47
	.4byte	0x97
	.uleb128 0x22
	.4byte	.LASF47
	.byte	0x1
	.byte	0x4f
	.4byte	0x62
	.uleb128 0x22
	.4byte	.LASF48
	.byte	0x1
	.byte	0x57
	.4byte	0x62
	.uleb128 0x22
	.4byte	.LASF49
	.byte	0x1
	.byte	0x5b
	.4byte	0x418
	.byte	0
	.uleb128 0x5
	.4byte	0x3fd
	.uleb128 0xd
	.byte	0x4
	.4byte	0x403
	.uleb128 0x5
	.4byte	0x1dd
	.uleb128 0x5
	.4byte	0x40d
	.uleb128 0xd
	.byte	0x4
	.4byte	0x413
	.uleb128 0x5
	.4byte	0xb7
	.uleb128 0xd
	.byte	0x4
	.4byte	0xa2
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF51
	.byte	0x1
	.byte	0x78
	.byte	0x1
	.4byte	.LFB39
	.4byte	.LFE39
	.4byte	.LLST8
	.byte	0x1
	.4byte	0x546
	.uleb128 0x18
	.4byte	.LASF53
	.byte	0x1
	.byte	0x78
	.4byte	0x546
	.4byte	.LLST9
	.uleb128 0x18
	.4byte	.LASF44
	.byte	0x1
	.byte	0x78
	.4byte	0x49
	.4byte	.LLST10
	.uleb128 0x23
	.ascii	"udp\000"
	.byte	0x1
	.byte	0x79
	.4byte	0x38f
	.4byte	.LLST11
	.uleb128 0x23
	.ascii	"ip\000"
	.byte	0x1
	.byte	0x7a
	.4byte	0x54d
	.4byte	.LLST12
	.uleb128 0x19
	.4byte	.LASF17
	.byte	0x1
	.byte	0x7b
	.4byte	0x558
	.4byte	.LLST13
	.uleb128 0x1c
	.4byte	0x2b5
	.4byte	.LBB29
	.4byte	.LBE29
	.byte	0x1
	.byte	0x7d
	.4byte	0x4cb
	.uleb128 0x1d
	.4byte	0x2c6
	.4byte	.LLST13
	.uleb128 0x1e
	.4byte	0x26f
	.4byte	.LBB31
	.4byte	.LBE31
	.byte	0x2
	.byte	0x25
	.uleb128 0x1d
	.4byte	0x281
	.4byte	.LLST15
	.uleb128 0x1b
	.4byte	.LBB32
	.4byte	.LBE32
	.uleb128 0x1f
	.4byte	0x28d
	.4byte	.LLST16
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x24
	.4byte	0x3a5
	.4byte	.LBB33
	.4byte	.Ldebug_ranges0+0x18
	.byte	0x1
	.byte	0x83
	.4byte	0x52f
	.uleb128 0x1d
	.4byte	0x3cb
	.4byte	.LLST17
	.uleb128 0x1d
	.4byte	0x3c0
	.4byte	.LLST18
	.uleb128 0x1d
	.4byte	0x3b6
	.4byte	.LLST19
	.uleb128 0x1a
	.4byte	.Ldebug_ranges0+0x38
	.uleb128 0x1f
	.4byte	0x3d6
	.4byte	.LLST20
	.uleb128 0x1f
	.4byte	0x3ec
	.4byte	.LLST21
	.uleb128 0x25
	.4byte	0x3e1
	.2byte	0x1100
	.uleb128 0x26
	.4byte	.LVL24
	.4byte	0x5f9
	.uleb128 0x21
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x21
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	.LVL25
	.4byte	0x61b
	.uleb128 0x21
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x21
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.4byte	0x54c
	.uleb128 0x27
	.uleb128 0x5
	.4byte	0x552
	.uleb128 0xd
	.byte	0x4
	.4byte	0x1dd
	.uleb128 0x5
	.4byte	0x82
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF54
	.byte	0x1
	.byte	0x8a
	.byte	0x1
	.4byte	.LFB40
	.4byte	.LFE40
	.4byte	.LLST22
	.byte	0x1
	.4byte	0x5a7
	.uleb128 0x18
	.4byte	.LASF55
	.byte	0x1
	.byte	0x8a
	.4byte	0x153
	.4byte	.LLST23
	.uleb128 0x18
	.4byte	.LASF56
	.byte	0x1
	.byte	0x8a
	.4byte	0x49
	.4byte	.LLST24
	.uleb128 0x26
	.4byte	.LVL29
	.4byte	0x41e
	.uleb128 0x21
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.byte	0
	.uleb128 0x28
	.4byte	.LASF57
	.byte	0x7
	.byte	0x25
	.4byte	0x5b3
	.byte	0
	.uleb128 0x5
	.4byte	0x15f
	.uleb128 0x8
	.4byte	0x119
	.4byte	0x5c3
	.uleb128 0x29
	.byte	0
	.uleb128 0x2a
	.4byte	.LASF58
	.byte	0x6
	.byte	0x55
	.4byte	0x5d0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	0x5b8
	.uleb128 0x2a
	.4byte	.LASF59
	.byte	0x6
	.byte	0x56
	.4byte	0x5e2
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	0x5b8
	.uleb128 0x2b
	.4byte	.LASF60
	.byte	0x1
	.byte	0x8e
	.4byte	0x3a0
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__udp_socket7
	.uleb128 0x2c
	.byte	0x1
	.4byte	.LASF64
	.byte	0x7
	.byte	0x59
	.byte	0x1
	.4byte	0x49
	.byte	0x1
	.4byte	0x61b
	.uleb128 0xc
	.4byte	0x62
	.uleb128 0xc
	.4byte	0x546
	.uleb128 0xc
	.4byte	0x97
	.byte	0
	.uleb128 0x2d
	.byte	0x1
	.4byte	.LASF65
	.byte	0x7
	.byte	0x58
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.4byte	0x546
	.uleb128 0xc
	.4byte	0x49
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB37
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LFE37
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL8
	.4byte	.LVL12
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL12
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL14
	.4byte	.LFE37
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL1
	.4byte	.LVL8
	.2byte	0x2
	.byte	0x70
	.sleb128 2
	.4byte	.LVL8
	.4byte	.LVL11-1
	.2byte	0x5
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x23
	.uleb128 0x2
	.4byte	.LVL12
	.4byte	.LVL14
	.2byte	0x2
	.byte	0x70
	.sleb128 2
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL3
	.4byte	.LVL10
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL12
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL6
	.4byte	.LVL7
	.2byte	0x3
	.byte	0x71
	.sleb128 -8
	.byte	0x9f
	.4byte	.LVL7
	.4byte	.LVL9
	.2byte	0x3
	.byte	0x71
	.sleb128 0
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL4
	.4byte	.LVL8
	.2byte	0x2
	.byte	0x70
	.sleb128 4
	.4byte	.LVL8
	.4byte	.LVL11-1
	.2byte	0x5
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x23
	.uleb128 0x4
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL4
	.4byte	.LVL5
	.2byte	0x9
	.byte	0x70
	.sleb128 4
	.byte	0x94
	.byte	0x2
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL5
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL6
	.4byte	.LVL8
	.2byte	0x9
	.byte	0x70
	.sleb128 4
	.byte	0x94
	.byte	0x2
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL8
	.4byte	.LVL11-1
	.2byte	0xc
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x23
	.uleb128 0x4
	.byte	0x94
	.byte	0x2
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL6
	.4byte	.LVL7
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL7
	.4byte	.LVL9
	.2byte	0x3
	.byte	0x71
	.sleb128 8
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LFB39
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI1
	.4byte	.LFE39
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LLST9:
	.4byte	.LVL15
	.4byte	.LVL21
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL21
	.4byte	.LVL22
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x3
	.byte	0x71
	.sleb128 16
	.byte	0x9f
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x3
	.byte	0x74
	.sleb128 8
	.byte	0x9f
	.4byte	.LVL26
	.4byte	.LFE39
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL15
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL18
	.4byte	.LFE39
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL16
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL26
	.4byte	.LFE39
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x38
	.byte	0x1c
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL16
	.4byte	.LVL21
	.2byte	0x3
	.byte	0x70
	.sleb128 -28
	.byte	0x9f
	.4byte	.LVL21
	.4byte	.LVL22
	.2byte	0x3
	.byte	0x71
	.sleb128 -28
	.byte	0x9f
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x3
	.byte	0x71
	.sleb128 -12
	.byte	0x9f
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x3
	.byte	0x74
	.sleb128 -20
	.byte	0x9f
	.4byte	.LVL26
	.4byte	.LFE39
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x4c
	.byte	0x1c
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL16
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LVL16
	.4byte	.LVL27
	.2byte	0x7
	.byte	0x75
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LVL17
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LLST17:
	.4byte	.LVL20
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST18:
	.4byte	.LVL20
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL26
	.4byte	.LFE39
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x38
	.byte	0x1c
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST19:
	.4byte	.LVL20
	.4byte	.LVL21
	.2byte	0x3
	.byte	0x70
	.sleb128 -28
	.byte	0x9f
	.4byte	.LVL21
	.4byte	.LVL22
	.2byte	0x3
	.byte	0x71
	.sleb128 -28
	.byte	0x9f
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x3
	.byte	0x71
	.sleb128 -12
	.byte	0x9f
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x3
	.byte	0x74
	.sleb128 -20
	.byte	0x9f
	.4byte	.LVL26
	.4byte	.LFE39
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x4c
	.byte	0x1c
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST20:
	.4byte	.LVL20
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL23
	.4byte	.LVL24-1
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST21:
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x3
	.byte	0x74
	.sleb128 -8
	.byte	0x9f
	.4byte	.LVL26
	.4byte	.LFE39
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x40
	.byte	0x1c
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST22:
	.4byte	.LFB40
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LFE40
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST23:
	.4byte	.LVL28
	.4byte	.LVL29-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL29-1
	.4byte	.LFE40
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST24:
	.4byte	.LVL28
	.4byte	.LVL29-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL29-1
	.4byte	.LFE40
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB16
	.4byte	.LBE16
	.4byte	.LBB22
	.4byte	.LBE22
	.4byte	0
	.4byte	0
	.4byte	.LBB33
	.4byte	.LBE33
	.4byte	.LBB37
	.4byte	.LBE37
	.4byte	.LBB38
	.4byte	.LBE38
	.4byte	0
	.4byte	0
	.4byte	.LBB34
	.4byte	.LBE34
	.4byte	.LBB35
	.4byte	.LBE35
	.4byte	.LBB36
	.4byte	.LBE36
	.4byte	0
	.4byte	0
	.4byte	.LFB37
	.4byte	.LFE37
	.4byte	.LFB39
	.4byte	.LFE39
	.4byte	.LFB40
	.4byte	.LFE40
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF45:
	.ascii	"udp_checksum\000"
.LASF46:
	.ascii	"result\000"
.LASF39:
	.ascii	"ntohs\000"
.LASF2:
	.ascii	"short int\000"
.LASF13:
	.ascii	"size_t\000"
.LASF17:
	.ascii	"udp_len\000"
.LASF12:
	.ascii	"sizetype\000"
.LASF54:
	.ascii	"udp_echo\000"
.LASF37:
	.ascii	"ip_dst\000"
.LASF43:
	.ascii	"socket\000"
.LASF42:
	.ascii	"dport\000"
.LASF15:
	.ascii	"udp_sport\000"
.LASF40:
	.ascii	"value\000"
.LASF62:
	.ascii	"udp.c\000"
.LASF41:
	.ascii	"htons\000"
.LASF47:
	.ascii	"checksum\000"
.LASF22:
	.ascii	"udp_port\000"
.LASF32:
	.ascii	"ip_id\000"
.LASF9:
	.ascii	"long long int\000"
.LASF60:
	.ascii	"__udp_socket7\000"
.LASF35:
	.ascii	"ip_sum\000"
.LASF48:
	.ascii	"zeroes_protocol\000"
.LASF6:
	.ascii	"long int\000"
.LASF24:
	.ascii	"s_addr\000"
.LASF38:
	.ascii	"__REV16\000"
.LASF56:
	.ascii	"udp_payload_len\000"
.LASF57:
	.ascii	"IP_ADDRESS_UNSPECIFIED\000"
.LASF25:
	.ascii	"s_bytes\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF36:
	.ascii	"ip_src\000"
.LASF0:
	.ascii	"signed char\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF7:
	.ascii	"uint32_t\000"
.LASF11:
	.ascii	"unsigned int\000"
.LASF4:
	.ascii	"uint16_t\000"
.LASF61:
	.ascii	"GNU C 4.7.1\000"
.LASF18:
	.ascii	"udp_sum\000"
.LASF58:
	.ascii	"__udp_sockets\000"
.LASF29:
	.ascii	"ip_vhl\000"
.LASF59:
	.ascii	"__udp_sockets_end\000"
.LASF63:
	.ascii	"/Users/pnr/Ell-i/Runtime/stm32/libraries/CoAP\000"
.LASF21:
	.ascii	"udp_socket_handler\000"
.LASF55:
	.ascii	"udp_payload\000"
.LASF49:
	.ascii	"srcp\000"
.LASF30:
	.ascii	"ip_tos\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF23:
	.ascii	"in_addr_t\000"
.LASF20:
	.ascii	"udp_socket\000"
.LASF34:
	.ascii	"ip_p\000"
.LASF53:
	.ascii	"payload\000"
.LASF8:
	.ascii	"long unsigned int\000"
.LASF28:
	.ascii	"ip_foff\000"
.LASF27:
	.ascii	"ip_off\000"
.LASF52:
	.ascii	"udp_packet\000"
.LASF3:
	.ascii	"uint8_t\000"
.LASF50:
	.ascii	"udp_input\000"
.LASF26:
	.ascii	"in_addr\000"
.LASF31:
	.ascii	"ip_len\000"
.LASF44:
	.ascii	"payload_len\000"
.LASF51:
	.ascii	"udp_output\000"
.LASF16:
	.ascii	"udp_dport\000"
.LASF14:
	.ascii	"udp_port_t\000"
.LASF64:
	.ascii	"ip_checksum\000"
.LASF33:
	.ascii	"ip_ttl\000"
.LASF19:
	.ascii	"udp_data\000"
.LASF65:
	.ascii	"ip_output\000"
	.ident	"GCC: (GNU) 4.7.1"
