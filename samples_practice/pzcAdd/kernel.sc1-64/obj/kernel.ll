# 1 "obj/kernel.pzs"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 299 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "obj/kernel.pzs" 2
 .text




# 1 "/opt/pzsdk.ver3.0/inc/pzc_boot.h" 1
# 155 "/opt/pzsdk.ver3.0/inc/pzc_boot.h"
.boot
PZC_TOP:
PZC_TOP0:
  i.movhi r24, (PZC_ARGUMENT0); i.ori r24,r24,(PZC_ARGUMENT0);
  c.j .INIT_PROLOGUE

PZC_TOP1:
  i.movhi r24, (PZC_ARGUMENT1); i.ori r24,r24,(PZC_ARGUMENT1);
  c.j .INIT_PROLOGUE

PZC_TOP2:
  i.movhi r24, (PZC_ARGUMENT2); i.ori r24,r24,(PZC_ARGUMENT2);
  c.j .INIT_PROLOGUE

PZC_TOP3:
  i.movhi r24, (PZC_ARGUMENT3); i.ori r24,r24,(PZC_ARGUMENT3);
  c.j .INIT_PROLOGUE

.INIT_PROLOGUE:
  i.xor zr zr zr
  f.movhi f0 0


  c.prefetch 1 r24 0
  c.nop


  c.jal .INIT_STACK
  c.nop


  c.chgthread
  c.nop


  i.eldd x4 r24 ((0x80)+0)
  i.eldd x5 r24 ((0x80)+8)
  i.eldd x6 r24 ((0x80)+16)
  i.eldd x7 r24 ((0x80)+24)

  d.eldd d4 r24 ((0xA0)+0)
  d.eldd d5 r24 ((0xA0)+8)
  d.eldd d6 r24 ((0xA0)+16)
  d.eldd d7 r24 ((0xA0)+24)

  i.eld r29 r24 0x10
  c.nop

  i.sfeqi r29 0
  c.nop

  c.nop
  c.bf .call_func

  i.xor r30 r30 r30
  i.slli r31 r29 2





  i.addi r28 r24 (0xC0)-4
  i.add r28 r28 r31


.push_stack:
  i.eld r31 r28 0
  c.nop

  i.addi r30 r30 1
  c.nop

  i.sfltu r30 r29
  c.nop

 i.sw sp 0 r31




 i.addi r28 r28 -4
 i.addi sp sp -4

 c.bf .push_stack





 i.addi sp sp 4
 c.nop


.call_func:
 i.eld r28 r24 0x8
 c.nop

 c.sync 3

 c.nop
 c.jalr r28

.call_func_ret:
 c.nop
 c.j abort

abort:


 c.nop
 c.sync 8


abort1:
 c.nop
 c.halt

 c.nop
 c.j abort1

exit_error:
 i.getpid r28; i.gettid r29; i.slli r28 r28 3; i.andi r28 r28 32760; i.or r28 r28 r29; i.movhi r30 (0x8000|((1) & 0x7FFF)); i.or r28 r28 r30; i.mtspr 1 r28;



 c.nop
 c.sync 8


exit_error1:
 c.nop
 c.halt

 c.nop
 c.j exit_error1

exit_stack_error:
 i.getpid r28; i.gettid r29; i.slli r28 r28 3; i.andi r28 r28 32760; i.or r28 r28 r29; i.movhi r30 (0x8000|((2) & 0x7FFF)); i.or r28 r28 r30; i.mtspr 1 r28;



 c.nop
 c.sync 8


exit_stack_error1:
 c.nop
 c.halt

 c.nop
 c.j exit_stack_error1


.INIT_STACK:
 i.gettid r28
 i.eld r30 r24 0xC


 i.sfnei r30 0
 c.bf setup_sp_limit


 i.movhi r30, (((2048))>>16); i.ori r30,r30,(((2048))&0xffff);

setup_sp_limit:
 i.mul r28 r28 r30

 i.getmaxtid r29
 i.mul r29 r29 r30
 i.addi r29 r29 -8
# 336 "/opt/pzsdk.ver3.0/inc/pzc_boot.h"
 i.sub sp r29 r28
 c.nop

 i.muli r31 r30 -1

 i.mov r5 sp
 i.add r4 sp r31


 c.nop
 c.ret

.argument

PZC_ARGUMENT0:
PZC_ARGUMENT:
PZC_MODE:
 .long 0
 .long ((0xC001<<16) | 2)
PZC_FUNC:
 .long 0
 .long (2048)
PZC_ARGC:
 .long 0
 .long 0
 .long 0
 .long 0

PZC_CTRL:
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0


PZC_ARG0:
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0


 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0




PZC_ARGUMENT1:
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0



PZC_ARGUMENT2:
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0




PZC_ARGUMENT3:
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0

 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0
 .long 0


.text
# 6 "obj/kernel.pzs" 2

 .file "obj/kernel.o"
 .section .rodata.cst8,"aM",@progbits,8
 .align 8
CPI0_0:
 .quad 9221120237041090560
 .text
 .globl __divdf3
 .align 8
 .type __divdf3,@function
__divdf3:
.function __divdf3,Double,Double,Double

 i.addi sp sp -192
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 56 x8
 i.sd sp 48 x9
 i.sd sp 40 x10
 i.sd sp 32 x11
 i.sd sp 24 x12
 i.sd sp 16 x13
 i.sd sp 8 x14
 i.sd sp 0 x15
 d.sd sp 72 d4
 i.movhi r21 32768
 i.movhi r14 65535
 i.ldd x13 sp 72
 d.sd sp 64 d5
 i.mov r20 zr
 i.ori r19 r14 65535
 i.ldd x14 sp 64
 i64.srli x4 x13 52
 i64.srli x5 x14 52
 i.andi r8 r8 2047
 i.andi r9 r10 2047
 i.xor r11 r29 r27
 i.sw sp 152 r8
 i.sw sp 160 r14
 i.movhi r14 15
 i.addi r16 r8 -1
 i.xor r10 r28 r26
 i.sfgtui r16 2045
 i.and r13 r11 r21
 i.and r12 r10 r20
 i.mov r10 r19
 i.ori r11 r14 65535
 i.and r15 r27 r11
 i.and r23 r29 r11
 i.and r14 r26 r10
 i.and r22 r28 r10
 c.bf LBB0_3

 i.addi r16 r9 -1
 i.sfltui r16 2046
 c.bnf LBB0_3

 i.sw sp 156 r9
 i.sd sp 168 x9
 i.sd sp 176 x6
LBB0_23:
 i.movhi r9 16
 i.movhi r16 29956
 i64.slli x14 x7 2
 i.mov r8 zr
 i.ori r16 r16 62259
 i.or r25 r23 r9
 i.or r24 r22 r8
 i.mov r9 r8
 i64.srli x13 x12 21
 i64.srli p0 x4 32
 i.sub r16 r16 r26
 i.mulhiu r19 r16 r26
 i64.srli x9 x9 32
 i64.sub x4 p0 x9
 i.mul r19 r8 r16
 i.mulhiu r9 r8 r16
 i64.srli x4 x4 32
 i64.srli x9 x9 32
 i64.slli x4 x4 32
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 31
 i.mulhiu r17 r8 r26
 i64.srli x8 x8 32
 i64.sub x8 p0 x8
 i.mul r19 r16 r8
 i.mulhiu r9 r16 r8
 i64.srli x4 x4 32
 i64.srli x9 x9 32
 i64.slli x4 x4 32
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 31
 i.mulhiu r17 r8 r26
 i64.srli x8 x8 32
 i64.sub x8 p0 x8
 i.mul r19 r16 r8
 i.mulhiu r9 r16 r8
 i64.srli x4 x4 32
 i64.srli x9 x9 32
 i64.slli x4 x4 32
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 31
 i64.slli x8 x11 11
 i.addi r8 r8 -1
 i.mulhiu r23 r8 r26
 i.mul r19 r8 r26
 i.mulhiu r17 r8 r16
 i64.srli p1 x11 32
 i64.srli x9 x9 32
 i64.srli x8 x8 32
 i64.slli x11 p1 32
 i.or r27 r19 r23
 i.or r26 r18 r22
 i64.add x8 x13 x8
 i64.sub x8 p0 x8
 i64.srli x9 x8 32
 i.mul r23 r18 r8
 i.mulhiu r19 r18 r8
 i.mulhiu r9 r16 r8
 i64.srli p0 x9 32
 i64.srli x11 x11 32
 i64.srli x4 x4 32
 i64.slli x9 p0 32
 i.or r27 r23 r19
 i.or r26 r22 r18
 i.movhi r22 64
 i64.srli x9 x7 30
 i64.add x4 x13 x4
 i.ori r23 r22 0
 i64.addi x13 x4 -2
 i64.srli x11 x11 32
 i64.srli x8 x13 32
 i.or r13 r19 r23
 i.mul r9 r16 r28
 i.or r12 r18 r22
 i64.srli x15 x4 32
 i.mulhiu r9 r16 r28
 i.mulhiu r19 r26 r12
 i64.srli x4 x4 32
 i64.srli p0 x9 32
 i.mulhiu r19 r26 r28
 i64.slli x4 x4 32
 i64.slli x14 p0 32
 i64.srli p0 x9 32
 i.or r23 r31 r9
 i.or r22 r30 r8
 i.mul r9 r26 r12
 i.mulhiu r27 r16 r12
 i.mul r13 r16 r12
 i64.srli p1 x13 32
 i64.srli x4 x4 32
 i64.srli x6 x6 32
 i.or r27 r9 r29
 i64.slli x8 p1 32
 i.or r26 r8 r28
 i.or r9 r13 r17
 i.or r8 r12 r16
 i.ld r12 sp 152
 i.ld r13 sp 156
 i.movhi r17 31
 i.sub r12 r12 r13
 i.add r16 r20 r12
 i.ld r12 sp 160
 i.ldd x14 sp 168
 i.ori r13 r12 65532
 i64.srli x6 x6 32
 i.and r19 r23 r13
 i.and r18 r22 r12
 i64.add x6 p0 x9
 i64.srli x9 x14 32
 i64.srli p0 x13 32
 i.and r21 r27 r19
 i64.add x4 p0 x4
 i.and r20 r26 r18
 i64.srli x9 x11 32
 i64.add x6 x6 x10
 i.mov r20 r29
 i64.add x4 x4 x9
 i64.srli x6 x6 32
 i.ori r21 r17 65535
 i64.add x9 x4 x6
 i64.sfgtu x9 x10
 c.bf LBB0_25

 i64.slli x4 x7 53
 i64.srli x7 x12 32
 i.mulhiu r12 r18 r24
 i.addi r16 r16 -1
 i.mul r13 r18 r14
 i64.srli x7 x9 32
 i.add r12 r12 r13
 i.mul r13 r14 r24
 i.mul r15 r18 r24
 i.add r13 r12 r13
 i64.srli x7 x7 32
 i64.srli x6 x6 32
 i64.slli x6 x6 32
 i.or r21 r15 r13
 i.or r20 r14 r12
 i64.sub p0 x4 x10
 c.j LBB0_26
LBB0_3:
 i.sw sp 156 r9
 i.mov r8 r19
 i.movhi r16 32767
 i.sd sp 184 x7
 i64.mov x7 x9
 i.ori r9 r16 65535
 i.movhi r16 0
 i.and r31 r27 r9
 i.and r25 r29 r9
 i.ori r18 r16 1
 i.movhi r17 32752
 i.and r30 r26 r8
 i.ori r19 r17 0
 i.and r24 r28 r8
 i64.sfltu x15 x9
 c.bf LBB0_5

 i.movhi r9 8
 i.mov r8 zr
 i.or r11 r27 r9
 i.or r10 r26 r8
 i.sd sp 144 x5
 d.ldd d4 sp 144
 c.j LBB0_31
LBB0_25:
 i64.srli x4 x9 33
 i64.slli x6 x7 52
 i64.srli x9 x9 1
 i64.srli x7 x12 32
 i.mul r14 r18 r14
 i.mulhiu r15 r18 r24
 i.mul r8 r8 r24
 i.add r14 r15 r14
 i.add r9 r14 r8
 i.mul r15 r18 r24
 i64.srli x4 x4 32
 i64.srli x7 x7 32
 i64.slli x4 x4 32
 i.or r21 r15 r9
 i.or r20 r14 r8
 i64.sub p0 x6 x10
LBB0_26:
 i.addi r15 r16 1023
 i.sfltsi r15 2047
 c.bf LBB0_28

 i.ldd x6 sp 176
 i.movhi r9 32752
 i.mov r8 zr
 i.or r11 r13 r9
 i.or r10 r12 r8
 i.sd sp 104 x5
 d.ldd d4 sp 104
 c.j LBB0_31
LBB0_28:
 i.sfgtsi r15 0
 c.bf LBB0_30
 c.j LBB0_29
LBB0_30:
 i.mov r10 r29
 i64.slli x4 p0 1
 i.and r13 r19 r11
 i64.sfgtu x4 x12
 i.mov r8 zr
 i.xori r9 zr 1
 i.and r12 r18 r10
 i64.srli x5 x7 32
 i64.slli x5 x5 52
 i.select r9 r9 r8
 i.or r15 r11 r13
 i64.srli x4 x4 32
 i.or r14 r10 r12
 i.ldd x6 sp 176
 i64.add x4 x7 x4
 i.or r11 r9 r13
 i.or r10 r8 r12
 i.sd sp 88 x5
 d.ldd d4 sp 88
 c.j LBB0_31
LBB0_5:
 i.sd sp 168 x7
 i64.sfltu x12 x9
 c.bf LBB0_7

 i.movhi r9 8
 i.mov r8 zr
 i.or r11 r29 r9
 i.or r10 r28 r8
 i.sd sp 136 x5
 d.ldd d4 sp 136
 c.j LBB0_31
LBB0_7:
 i.mov r16 zr
 i64.sfne x15 x8
 c.bf LBB0_11

 i.movhi r8 CPI0_0
 i.mov r16 zr
 i.ori r9 r8 CPI0_0
 i64.sfeq x12 x8
 c.bnf LBB0_10

 i64.srli p0 x4 32
 d.eldd d4 p0 0
 c.j LBB0_31
LBB0_29:
 i.ldd x4 sp 176
 i.sd sp 96 x4
 d.ldd d4 sp 96
 c.j LBB0_31
LBB0_11:
 i.mov r19 zr
 i64.mov x4 x8
 i.mov r8 r19
 i64.sfne x12 x4
 c.bf LBB0_13

 i.sd sp 120 x6
 d.ldd d4 sp 120
 c.j LBB0_31
LBB0_10:
 i.mov r20 zr
 i.and r9 r29 r21
 i.and r8 r28 r20
 i.xor r11 r9 r27
 i.xor r10 r8 r26
 i.sd sp 128 x5
 d.ldd d4 sp 128
 c.j LBB0_31
LBB0_13:
 i64.srli x4 x9 32
 i64.sfne x15 x4
 c.bf LBB0_15
 c.j LBB0_14
LBB0_15:
 i.mov r9 zr
 i64.srli x4 x4 32
 i64.sfne x12 x4
 c.bf LBB0_17
 c.j LBB0_16
LBB0_17:
 i.ldd x4 sp 168
 i.mov r20 zr
 i.mov r10 r9
 i64.sfgtu x15 x5
 c.bnf LBB0_19

 i.sd sp 176 x6
 i.ldd x4 sp 168
 i.ldd x7 sp 184
 c.j LBB0_20
LBB0_14:
 i.movhi r8 CPI0_0
 i.sd sp 112 x6
 i.ori r9 r8 CPI0_0
 d.ldd d1 sp 112
 i64.srli p0 x4 32
 i.mov r9 zr
 d.eldd d2 p0 0
 i64.srli x4 x4 32
 i64.sfne x12 x4
 f.select f8 f2 f4
 f.select f9 f3 f5
 c.j LBB0_31
LBB0_16:
 i.mov r16 zr
 i.or r9 r13 r17
 i.or r8 r12 r16
 i.sd sp 80 x4
 d.ldd d4 sp 80
LBB0_31:
 i.ldd x15 sp 0
 i.ldd x14 sp 8
 i.ldd x13 sp 16
 i.ldd x12 sp 24
 i.ldd x11 sp 32
 i.ldd x10 sp 40
 i.ldd x9 sp 48
 i.ldd x8 sp 56
 i.addi sp sp 192
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
LBB0_19:
 i.sd sp 176 x6
 i.ldd x7 sp 184
 i64.srli x4 x7 1
 i.or r17 r15 r9
 i.or r16 r14 r8
 i64.srli x4 x8 2
 i.or r19 r17 r9
 i.or r18 r16 r8
 i64.srli x4 x9 4
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 8
 i.or r19 r17 r9
 i.or r18 r16 r8
 i64.srli x4 x9 16
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 32
 i.or r19 r17 r9
 i.or r18 r16 r8
 i.xori r8 r18 -1
 i.xori r9 r19 -1
 i.movhi r18 21845
 i.ori r18 r18 21845
 i64.srli x8 x4 1
 i.mov r19 r18
 i.and r21 r17 r19
 i.and r20 r16 r18
 i.movhi r16 13107
 i.ori r16 r16 13107
 i64.sub x4 x4 x10
 i.mov r17 r16
 i.and r19 r9 r17
 i.and r18 r8 r16
 i64.srli x4 x4 2
 i.and r21 r9 r17
 i.and r20 r8 r16
 i64.add x4 x9 x10
 i64.srli x8 x4 4
 i64.add x4 x4 x8
 i.movhi r16 3855
 i.ori r16 r16 3855
 i.mov r17 r16
 i.and r19 r9 r17
 i.and r18 r8 r16
 i.movhi r8 257
 i.ori r8 r8 257
 i.mul r9 r18 r8
 i.mulhiu r16 r18 r8
 i.add r9 r16 r9
 i64.srli x8 x9 32
 i.mul r8 r16 r8
 i.add r9 r9 r8
 i64.srli x4 x4 32
 i64.slli x4 x4 32
 i64.srli x4 x4 56
 i.addi r17 r8 -11
 i64.srli x8 x8 32
 i64.sll x7 x7 x8
 i.xori r16 zr 12
 i.sub r20 r16 r8
 i.ldd x4 sp 168
LBB0_20:
 i.mov r10 r9
 i64.sfgtu x12 x5
 c.bnf LBB0_22

 i.sd sp 168 x4
 c.j LBB0_23
LBB0_22:
 i.sd sp 168 x4
 i64.srli x4 x11 1
 i.or r17 r23 r9
 i.or r16 r22 r8
 i64.srli x4 x8 2
 i.or r19 r17 r9
 i.or r18 r16 r8
 i64.srli x4 x9 4
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 8
 i.or r19 r17 r9
 i.or r18 r16 r8
 i64.srli x4 x9 16
 i.or r17 r19 r9
 i.or r16 r18 r8
 i64.srli x4 x8 32
 i.or r19 r17 r9
 i.or r18 r16 r8
 i.xori r8 r18 -1
 i.xori r9 r19 -1
 i.movhi r18 21845
 i.ori r18 r18 21845
 i64.srli x8 x4 1
 i.mov r19 r18
 i.and r25 r17 r19
 i.and r24 r16 r18
 i.movhi r16 13107
 i.ori r16 r16 13107
 i64.sub x4 x4 x12
 i.mov r17 r16
 i.and r19 r9 r17
 i.and r18 r8 r16
 i64.srli x4 x4 2
 i.and r25 r9 r17
 i.and r24 r8 r16
 i64.add x4 x9 x12
 i64.srli x8 x4 4
 i64.add x4 x4 x8
 i.movhi r16 3855
 i.ori r16 r16 3855
 i.mov r17 r16
 i.and r19 r9 r17
 i.and r18 r8 r16
 i.movhi r8 257
 i.ori r8 r8 257
 i.mul r9 r18 r8
 i.mulhiu r16 r18 r8
 i.add r9 r16 r9
 i64.srli x8 x9 32
 i.mul r8 r16 r8
 i.add r9 r9 r8
 i64.srli x4 x4 32
 i64.slli x4 x4 32
 i64.srli x4 x4 56
 i.addi r17 r8 -11
 i.add r8 r20 r8
 i64.srli x8 x8 32
 i.addi r20 r8 -12
 i64.sll x11 x11 x8
 c.j LBB0_23
.tmp0:
 .size __divdf3, .tmp0-__divdf3

 .globl __ashldi3
 .align 8
 .type __ashldi3,@function
__ashldi3:
.function __ashldi3,Int64,Int64,Int32

 i.andi r11 r10 32
 i.sfeqi r11 0
 c.bf LBB1_2

 i.addi r10 r10 -32
 i.sll r9 r8 r10
 i.mov r11 zr
 i64.srli x5 x5 32
 c.j LBB1_5
LBB1_2:
 i.sfeqi r10 0
 c.bnf LBB1_4

 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
LBB1_4:
 i64.srli x6 x4 32
 i.xori r11 zr 32
 i.sll r15 r8 r10
 i.sll r12 r12 r10
 i.sub r10 r11 r10
 i.srl r8 r8 r10
 i64.srli x5 x7 32
 i.or r9 r12 r8
LBB1_5:
 i64.srli x4 x4 32
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 i64.slli x6 x4 32
 i.or r9 r13 r11
 i.or r8 r12 r10
 c.ret
.tmp1:
 .size __ashldi3, .tmp1-__ashldi3

 .globl __lshrdi3
 .align 8
 .type __lshrdi3,@function
__lshrdi3:
.function __lshrdi3,Int64,Int64,Int32

 i64.srli x6 x4 32
 i.andi r11 r10 32
 i.sfeqi r11 0
 c.bf LBB2_2

 i.addi r8 r10 -32
 i.mov r11 zr
 i.srl r9 r12 r8
 i64.srli x5 x5 32
 c.j LBB2_5
LBB2_2:
 i.sfeqi r10 0
 c.bnf LBB2_4

 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
LBB2_4:
 i.xori r11 zr 32
 i.srl r15 r12 r10
 i.srl r8 r8 r10
 i.sub r11 r11 r10
 i.sll r11 r12 r11
 i.or r9 r11 r8
 i64.srli x5 x7 32
 i64.slli x5 x5 32
LBB2_5:
 i64.srli x6 x4 32
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 i.or r9 r13 r11
 i.or r8 r12 r10
 c.ret
.tmp2:
 .size __lshrdi3, .tmp2-__lshrdi3

 .globl __divdi3
 .align 8
 .type __divdi3,@function
__divdi3:
.function __divdi3,Int64,Int64,Int64

 i.addi sp sp -24
 i64.srai x6 x4 63
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.ldret lr
 i.sw sp 16 lr
 i.sd sp 8 x8
 i.sd sp 0 x9
 i.xor r15 r11 r9
 i64.srai x8 x5 63
 i.xor r19 r13 r9
 i.xor r14 r10 r8
 i.xor r18 r12 r8
 i64.sub x4 x9 x6
 i.xor r13 r17 r11
 i.xor r12 r16 r10
 i64.sub x5 x6 x8
 i.mov r13 zr
 i64.srai x8 x7 63
 i64.srli x6 x6 32
 c.jal __udivmoddi4
 i.xor r11 r9 r17
 i.ldd x9 sp 0
 i.xor r10 r8 r16
 i64.sub x4 x5 x8
 i.ldd x8 sp 8
 i.ld lr sp 16
 c.nop
 i.stret lr
 i.addi sp sp 24
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp3:
 .size __divdi3, .tmp3-__divdi3

 .globl __udivmoddi4
 .align 8
 .type __udivmoddi4,@function
__udivmoddi4:
.function __udivmoddi4,Int64,Int64,Int64,Pointer

 i.addi sp sp -56
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 48 x8
 i64.srli x8 x4 32
 i64.srli x7 x5 32
 i.sd sp 40 x9
 i.sd sp 32 x10
 i.sd sp 24 x11
 i.sd sp 16 x12
 i.sd sp 8 x13
 i.sd sp 0 x14
 i.sfnei r16 0
 c.bf LBB4_7
 c.j LBB4_1
LBB4_7:
 i.sfnei r10 0
 c.bf LBB4_23
 c.j LBB4_8
LBB4_23:
 i.sfnei r14 0
 c.bf LBB4_29
 c.j LBB4_24
LBB4_29:
 i.srli r18 r14 1
 i.movhi r19 21845
 i.or r14 r14 r18
 i.ori r19 r19 21845
 i.srli r15 r14 2
 i.or r14 r14 r15
 i.srli r15 r14 4
 i.or r14 r14 r15
 i.srli r15 r14 8
 i.or r14 r14 r15
 i.srli r15 r14 16
 i.or r14 r14 r15
 i.srli r15 r16 1
 i.or r15 r16 r15
 i.xori r14 r14 -1
 i.srli r20 r15 2
 i.srli r18 r14 1
 i.or r15 r15 r20
 i.and r18 r18 r19
 i.srli r20 r15 4
 i.sub r14 r14 r18
 i.movhi r18 13107
 i.or r15 r15 r20
 i.ori r18 r18 13107
 i.srli r20 r15 8
 i.or r15 r15 r20
 i.and r20 r14 r18
 i.srli r14 r14 2
 i.srli r21 r15 16
 i.and r14 r14 r18
 i.or r15 r15 r21
 i.add r14 r20 r14
 i.xori r15 r15 -1
 i.srli r21 r14 4
 i.srli r20 r15 1
 i.add r14 r14 r21
 i.and r19 r20 r19
 i.sub r15 r15 r19
 i.movhi r19 3855
 i.srli r20 r15 2
 i.and r15 r15 r18
 i.ori r19 r19 3855
 i.and r18 r20 r18
 i.movhi r20 257
 i.and r14 r14 r19
 i.add r15 r15 r18
 i.srli r18 r15 4
 i.add r15 r15 r18
 i.ori r18 r20 257
 i.and r15 r15 r19
 i.mul r14 r14 r18
 i.mul r15 r15 r18
 i.srli r14 r14 24
 i.srli r15 r15 24
 i.sub r15 r14 r15
 i.sfltui r15 32
 c.bnf LBB4_20

 i.xori r18 zr 31
 i.addi r14 r15 1
 i.sub r22 r18 r15
 i.addi r15 r15 -31
 i.srl r20 r16 r14
 i.sll r19 r8 r22
 i.srai r15 r15 31
 i.srl r8 r8 r14
 i.sll r9 r16 r22
 i.and r8 r8 r15
 i.and r20 r20 r15
 i.or r8 r8 r9
 c.j LBB4_34
LBB4_1:
 i.sfnei r14 0
 c.bf LBB4_5
 c.j LBB4_2
LBB4_5:
 i.mov r11 zr
 i64.srli x7 x5 32
 i64.sfeq x6 x7
 c.bf LBB4_40

 i.movhi r10 65535
 i64.mov p0 x6
 i.ori r11 r10 65535
 i64.srli x5 x5 32
 i.and r15 r9 r11
 i.and r14 r8 r10
 i.esw p0 0 r14
 i.esw p0 4 r15
 c.j LBB4_22
LBB4_8:
 i.sfnei r14 0
 c.bf LBB4_11
 c.j LBB4_9
LBB4_11:
 i.sfnei r8 0
 c.bf LBB4_15
 c.j LBB4_12
LBB4_15:
 i.addi r18 r14 -1
 i.and r19 r18 r14
 i.sfnei r19 0
 c.bf LBB4_19
 c.j LBB4_16
LBB4_19:
 i.srli r18 r14 1
 i.movhi r19 21845
 i.or r14 r14 r18
 i.ori r19 r19 21845
 i.srli r15 r14 2
 i.or r14 r14 r15
 i.srli r15 r14 4
 i.or r14 r14 r15
 i.srli r15 r14 8
 i.or r14 r14 r15
 i.srli r15 r14 16
 i.or r14 r14 r15
 i.srli r15 r16 1
 i.or r15 r16 r15
 i.xori r14 r14 -1
 i.srli r20 r15 2
 i.srli r18 r14 1
 i.or r15 r15 r20
 i.and r18 r18 r19
 i.srli r20 r15 4
 i.sub r14 r14 r18
 i.movhi r18 13107
 i.or r15 r15 r20
 i.ori r18 r18 13107
 i.srli r20 r15 8
 i.or r15 r15 r20
 i.and r20 r14 r18
 i.srli r14 r14 2
 i.srli r21 r15 16
 i.and r14 r14 r18
 i.or r15 r15 r21
 i.add r14 r20 r14
 i.xori r15 r15 -1
 i.srli r21 r14 4
 i.srli r20 r15 1
 i.add r14 r14 r21
 i.and r19 r20 r19
 i.sub r15 r15 r19
 i.movhi r19 3855
 i.srli r20 r15 2
 i.and r15 r15 r18
 i.ori r19 r19 3855
 i.and r18 r20 r18
 i.movhi r20 257
 i.and r14 r14 r19
 i.add r15 r15 r18
 i.srli r18 r15 4
 i.add r15 r15 r18
 i.ori r18 r20 257
 i.and r15 r15 r19
 i.mul r14 r14 r18
 i.mul r15 r15 r18
 i.srli r14 r14 24
 i.srli r15 r15 24
 i.sub r15 r14 r15
 i.sfltui r15 31
 c.bf LBB4_33
LBB4_20:
 i.mov r11 zr
 i64.srli x7 x5 32
 i64.sfeq x6 x7
 c.bf LBB4_40

 i64.mov p0 x6
 i.esw p0 0 r8
 i.esw p0 4 r9
LBB4_22:
 i.mov r9 zr
 i64.srli x7 x4 32
 c.j LBB4_40
LBB4_24:
 i.addi r18 r10 -1
 i.and r14 r18 r10
 i.sfnei r14 0
 c.bf LBB4_31
 c.j LBB4_25
LBB4_31:
 i.srli r14 r10 1
 i.movhi r18 21845
 i.movhi r20 257
 i.xori r28 zr 31
 i.or r14 r10 r14
 i.ori r18 r18 21845
 i.ori r20 r20 257
 i.srli r15 r14 2
 i.or r14 r14 r15
 i.srli r15 r14 4
 i.or r14 r14 r15
 i.srli r15 r14 8
 i.or r14 r14 r15
 i.srli r15 r14 16
 i.or r14 r14 r15
 i.xori r14 r14 -1
 i.srli r15 r14 1
 i.and r15 r15 r18
 i.sub r14 r14 r15
 i.movhi r15 13107
 i.ori r15 r15 13107
 i.and r19 r14 r15
 i.srli r14 r14 2
 i.and r14 r14 r15
 i.add r14 r19 r14
 i.srli r19 r14 4
 i.add r14 r14 r19
 i.movhi r19 3855
 i.ori r19 r19 3855
 i.and r14 r14 r19
 i.mul r14 r14 r20
 i.srli r14 r14 24
 i.addi r24 r14 33
 i.srli r14 r16 1
 i.or r14 r16 r14
 i.srli r21 r14 2
 i.or r14 r14 r21
 i.srli r21 r14 4
 i.or r14 r14 r21
 i.srli r21 r14 8
 i.or r14 r14 r21
 i.srli r21 r14 16
 i.or r14 r14 r21
 i.xori r14 r14 -1
 i.srli r21 r14 1
 i.and r18 r21 r18
 i.sub r14 r14 r18
 i.and r18 r14 r15
 i.srli r14 r14 2
 i.and r14 r14 r15
 i.add r14 r18 r14
 i.xori r18 zr 64
 i.srli r15 r14 4
 i.add r14 r14 r15
 i.and r14 r14 r19
 i.mul r14 r14 r20
 i.xori r20 zr 32
 i.srli r15 r14 24
 i.sub r14 r24 r15
 i.sfeq r24 r15
 i.sub r25 r20 r14
 i.sub r18 r18 r14
 i.addi r21 r14 -33
 i.addi r26 r14 -32
 i.sub r28 r28 r14
 i.sll r19 r8 r18
 i.srai r20 r25 31
 i.srai r21 r21 31
 i.sll r18 r16 r18
 i.srai r27 r26 31
 i.srai r28 r28 31
 i.and r23 r19 r20
 i.sll r19 r8 r25
 i.and r19 r19 r21
 i.srl r21 r8 r26
 i.srl r26 r16 r26
 i.srl r8 r8 r14
 i.or r18 r18 r21
 i.and r9 r28 r26
 i.and r18 r18 r20
 i.srl r20 r16 r14
 i.sll r16 r16 r25
 i.or r8 r16 r8
 i.or r19 r18 r19
 i.and r20 r27 r20
 i.mov r17 zr
 i.and r8 r8 r27
 i.or r8 r9 r8
 c.bnf LBB4_35

 c.j LBB4_37
LBB4_2:
 i.mov r15 zr
 i64.srli x7 x7 32
 i64.sfeq x6 x7
 c.bf LBB4_4

 i.remu r15 r8 r10
 i64.mov p0 x6
 i64.srli x7 x7 32
 i.esw p0 0 r14
 i.esw p0 4 r15
LBB4_4:
 i.divu r9 r8 r10
 i64.srli x7 x4 32
 c.j LBB4_40
LBB4_9:
 i.mov r9 zr
 i64.srli x7 x4 32
 i64.sfeq x6 x7
 c.bf LBB4_40

 i.mov r9 zr
 i64.mov p0 x6
 i64.srli x7 x4 32
 i.esw p0 0 r14
 i.esw p0 4 r15
 c.j LBB4_40
LBB4_12:
 i.mov r9 zr
 i64.srli x4 x4 32
 i64.sfeq x6 x4
 c.bf LBB4_14

 i.remu r9 r16 r14
 i64.mov p0 x6
 i64.srli x4 x4 32
 i64.slli x4 x4 32
 i.esw p0 0 r8
 i.esw p0 4 r9
LBB4_14:
 i.divu r9 r16 r14
 i64.srli x7 x4 32
 c.j LBB4_40
LBB4_25:
 i.mov r15 zr
 i64.srli x7 x7 32
 i64.sfeq x6 x7
 c.bf LBB4_27

 i.and r15 r18 r8
 i64.mov p0 x6
 i64.srli x7 x7 32
 i.esw p0 0 r14
 i.esw p0 4 r15
LBB4_27:
 i64.mov x7 x4
 i.sfeqi r10 1
 c.bf LBB4_40

 i.nand r10 r10 r18
 i.movhi r12 21845
 i.srli r11 r10 1
 i.ori r12 r12 21845
 i.and r11 r11 r12
 i.sub r10 r10 r11
 i.movhi r11 13107
 i.ori r11 r11 13107
 i.and r12 r10 r11
 i.srli r10 r10 2
 i.and r10 r10 r11
 i.add r10 r12 r10
 i.srli r11 r10 4
 i.add r10 r10 r11
 i.movhi r11 3855
 i.ori r11 r11 3855
 i.and r10 r10 r11
 i.movhi r11 257
 i.ori r11 r11 257
 i.mul r10 r10 r11
 i.xori r11 zr 32
 i.srli r10 r10 24
 i.sub r11 r11 r10
 i.srl r13 r16 r10
 i.srl r8 r8 r10
 i.sll r11 r16 r11
 i.or r9 r11 r8
 i64.srli x5 x6 32
 i64.slli x5 x5 32
 i64.srli x4 x4 32
 i.or r15 r9 r11
 i.or r14 r8 r10
 c.j LBB4_40
LBB4_16:
 i.mov r11 zr
 i64.srli x5 x5 32
 i64.sfeq x6 x5
 c.bf LBB4_18

 i.movhi r19 65535
 i.and r11 r18 r16
 i64.mov p0 x6
 i.ori r21 r19 65535
 i64.srli x5 x5 32
 i64.srli x10 x10 32
 i64.slli x5 x5 32
 i.and r23 r9 r21
 i.and r22 r8 r20
 i.or r9 r11 r23
 i.or r8 r10 r22
 i.esw p0 0 r8
 i.esw p0 4 r9
LBB4_18:
 i.movhi r9 21845
 i.nand r8 r14 r18
 i.srli r10 r8 1
 i.ori r9 r9 21845
 i.and r9 r10 r9
 i.sub r8 r8 r9
 i.movhi r9 13107
 i.ori r9 r9 13107
 i.srli r10 r8 2
 i.and r8 r8 r9
 i.and r9 r10 r9
 i.movhi r10 257
 i.add r8 r8 r9
 i.srli r9 r8 4
 i.add r8 r8 r9
 i.movhi r9 3855
 i.ori r9 r9 3855
 i.and r8 r8 r9
 i.ori r9 r10 257
 i.mul r8 r8 r9
 i.srli r8 r8 24
 i.srl r9 r16 r8
 i64.srli x7 x4 32
 c.j LBB4_40
LBB4_33:
 i.xori r18 zr 31
 i.addi r14 r15 1
 i.sub r15 r18 r15
 i.srl r20 r16 r14
 i.sll r19 r8 r15
 i.sll r15 r16 r15
 i.srl r8 r8 r14
 i.or r8 r15 r8
LBB4_34:
 i.mov r23 zr
LBB4_35:
 i64.addi p0 x5 -1
 i.mov r17 zr
LBB4_36:

 i.slli r15 r20 1
 i.srli r20 r8 31
 i.slli r8 r8 1
 i.srli r9 r19 31
 i.addi r14 r14 -1
 i.or r21 r20 r15
 i.or r9 r8 r9
 i.slli r15 r19 1
 i.srli r18 r23 31
 i.sfnei r14 0
 i64.srli p1 x10 32
 i64.srli x4 x4 32
 i.or r19 r18 r15
 i.slli r15 r23 1
 i64.slli x10 p1 32
 i.or r23 r21 r9
 i.or r22 r20 r8
 i64.sub x4 p0 x11
 i64.srai x12 x4 63
 i.and r9 r25 r11
 i.and r8 r24 r10
 i64.sub x4 x11 x4
 i.or r23 r17 r15
 i.andi r17 r24 1
 i64.srli x10 x4 32
 c.bf LBB4_36
LBB4_37:
 i64.srli x7 x9 32
 i64.srli x5 x8 32
 i64.srli x8 x11 32
 i64.slli x7 x7 32
 i.or r19 r15 r17
 i.or r18 r14 r16
 i64.slli x7 x8 1
 i.mov r17 zr
 i64.srli p0 x9 31
 i64.srli x8 x8 32
 i64.sfeq x6 x8
 c.bf LBB4_39

 i.mov r17 r20
 i.mov r9 r8
 i64.srli p1 x8 32
 i64.srli x4 x4 32
 i64.slli x8 p1 32
 i64.mov p1 x6
 i.or r19 r17 r9
 i.or r18 r16 r8
 i.esw p1 0 r18
 i.esw p1 4 r19
LBB4_39:
 i.movhi r12 65535
 i64.slli x4 p0 32
 i.ori r13 r12 65534
 i64.srli x6 x6 32
 i.and r17 r15 r13
 i.and r16 r14 r12
 i.or r13 r9 r17
 i.or r12 r8 r16
 i.or r15 r13 r11
 i.or r14 r12 r10
LBB4_40:
 i64.mov x4 x7
 i.ldd x14 sp 0
 i.ldd x13 sp 8
 i.ldd x12 sp 16
 i.ldd x11 sp 24
 i.ldd x10 sp 32
 i.ldd x9 sp 40
 i.ldd x8 sp 48
 i.addi sp sp 56
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp4:
 .size __udivmoddi4, .tmp4-__udivmoddi4

 .globl __udivdi3
 .align 8
 .type __udivdi3,@function
__udivdi3:
.function __udivdi3,Int64,Int64,Int64

 i.addi sp sp -8
 i.mov r13 zr
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.ldret lr
 i.sw sp 0 lr
 i64.srli x6 x6 32
 c.jal __udivmoddi4
 i.ld lr sp 0
 c.nop
 i.stret lr
 i.addi sp sp 8
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp5:
 .size __udivdi3, .tmp5-__udivdi3

 .globl __moddi3
 .align 8
 .type __moddi3,@function
__moddi3:
.function __moddi3,Int64,Int64,Int64

 i.addi sp sp -24
 i64.srai x6 x5 63
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.ldret lr
 i.sw sp 16 lr
 i.sd sp 0 x8
 i64.srai x8 x4 63
 i.xor r15 r13 r11
 i.xor r14 r12 r10
 i64.sub x5 x7 x6
 i.xor r13 r17 r9
 i.xor r12 r16 r8
 i64.sub x4 x6 x8
 i.mov r7 sp
 i64.srai xtmp xtmp 32
 i64.mov x6 xtmp
 i64.addi x6 xtmp 8
 c.jal __udivmoddi4
 i.ldd x4 sp 8
 i.xor r11 r9 r17
 i.xor r10 r8 r16
 i64.sub x4 x5 x8
 i.ldd x8 sp 0
 i.ld lr sp 16
 c.nop
 i.stret lr
 i.addi sp sp 24
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp6:
 .size __moddi3, .tmp6-__moddi3

 .globl __umoddi3
 .align 8
 .type __umoddi3,@function
__umoddi3:
.function __umoddi3,Int64,Int64,Int64

 i.addi sp sp -16
 i.mov r7 sp
 i64.srai xtmp xtmp 32
 i64.mov x6 xtmp
 i64.addi x6 xtmp 0
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.ldret lr
 i.sw sp 8 lr
 c.jal __udivmoddi4
 i.ldd x4 sp 0
 i.ld lr sp 8
 c.nop
 i.stret lr
 i.addi sp sp 16
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp7:
 .size __umoddi3, .tmp7-__umoddi3

 .section .rodata.cst8,"aM",@progbits,8
 .align 8
CPI8_0:
 .quad -4382002437431492608
CPI8_1:
 .quad 4751297606875873280
 .text
 .globl __floatdidf
 .align 8
 .type __floatdidf,@function
__floatdidf:
.function __floatdidf,Double,Int64

 i.addi sp sp -24
 i.movhi r10 65535
 i.movhi r14 CPI8_0
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 8 x8
 i.movhi r16 CPI8_1
 d.mov dtmp a0
 d.sd sp 0 dtmp
 i.ori r11 r10 65535
 i.ori r15 r14 CPI8_0
 i64.srli x5 x5 32
 i64.srli p0 x7 32
 i.and r13 r9 r11
 d.eldd d1 p0 0
 i.and r12 r8 r10
 i.movhi r11 17200
 i64.srli x4 x4 32
 i.mov r10 zr
 d.itof d5 r8
 i.or r15 r13 r11
 i.or r14 r12 r10
 i.ori r11 r16 CPI8_1
 i64.srli p0 x5 32
 i.sd sp 16 x7
 d.eldd d2 p0 0
 d.ldd d4 sp 16
 d.mov a0 d1
 d.mad d1 d5 d2 a0
 d.ldd dtmp sp 0
 d.mov a0 dtmp
 i.ldd x8 sp 8
 d.add d4 d4 d1
 i.addi sp sp 24
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp8:
 .size __floatdidf, .tmp8-__floatdidf

 .section .rodata.cst8,"aM",@progbits,8
 .align 8
CPI9_0:
 .quad -4237887249354588160
 .text
 .globl __floatundidf
 .align 8
 .type __floatundidf,@function
__floatundidf:
.function __floatundidf,Double,Int64

 i.addi sp sp -24
 i.movhi r11 17712
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 0 x8
 i.movhi r16 65535
 i64.srli x6 x4 32
 i.ori r17 r16 65535
 i.mov r10 zr
 i.or r15 r13 r11
 i64.srli x8 x8 32
 i.or r14 r12 r10
 i.and r13 r9 r17
 i.movhi r11 17200
 i.and r12 r8 r16
 i.sd sp 8 x7
 i.movhi r14 CPI9_0
 i.or r9 r13 r11
 d.ldd d1 sp 8
 i.or r8 r12 r10
 i.ori r11 r14 CPI9_0
 i64.srli p0 x5 32
 i.sd sp 16 x4
 d.eldd d2 p0 0
 d.ldd d4 sp 16
 i.ldd x8 sp 0
 d.add d1 d1 d2
 d.add d4 d4 d1
 i.addi sp sp 24
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp9:
 .size __floatundidf, .tmp9-__floatundidf

 .globl __fixdfdi
 .align 8
 .type __fixdfdi,@function
__fixdfdi:
.function __fixdfdi,Int64,Double

 i.addi sp sp -24
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 8 x8
 i.sd sp 0 x9
 d.sd sp 16 d4
 i.ldd x5 sp 16
 i64.srli x4 x5 52
 i.andi r12 r8 2047
 i.mov r9 zr
 i.sfltui r12 1023
 c.bnf LBB10_2

 i64.srli x4 x4 32
 c.j LBB10_6
LBB10_2:
 i64.srli x7 x5 32
 i.addi r13 r12 -1023
 i.srai r9 r14 31
 b.lsbi r14 r14 19
 i.sfltsi r13 53
 b.seti r15 r14 20
 i64.srai x4 x4 32
 i64.srli x7 x7 32
 i64.slli x7 x7 32
 c.bf LBB10_4

 i.movhi r13 65535
 i.ori r17 r13 65535
 i.addi r13 r12 -1075
 i64.srli x8 x8 32
 i64.srli x6 x6 32
 i.and r19 r11 r17
 i.and r18 r10 r16
 i.or r11 r15 r19
 i.or r10 r14 r18
 i64.sll x5 x5 x6
 c.j LBB10_5
LBB10_4:
 i.movhi r13 65535
 i.ori r17 r13 65535
 i.xori r13 zr 1075
 i64.srli x8 x8 32
 i.sub r13 r13 r12
 i.and r19 r11 r17
 i64.srli x6 x6 32
 i.and r18 r10 r16
 i.or r11 r15 r19
 i.or r10 r14 r18
 i64.srl x5 x5 x6
LBB10_5:
 i64.srli x6 x5 32
 i.mov r11 r10
 i.mov r13 r12
 i64.srli x5 x5 32
 i64.srli x6 x6 32
 i64.slli x6 x6 32
 i.or r15 r13 r11
 i.or r14 r12 r10
 i.xor r11 r15 r9
 i.xor r10 r14 r8
 i64.sub x4 x5 x4
LBB10_6:
 i.ldd x9 sp 0
 i.ldd x8 sp 8
 i.addi sp sp 24
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp10:
 .size __fixdfdi, .tmp10-__fixdfdi

 .globl __fixsfdi
 .align 8
 .type __fixsfdi,@function
__fixsfdi:
.function __fixsfdi,Int64,Float

 f.ftoimv r11 f8
 i.srli r8 r11 23
 i.andi r10 r8 255
 i.mov r9 zr
 i.sfltui r10 127
 c.bnf LBB11_2

 i64.srli x4 x4 32
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
LBB11_2:
 i.srai r9 r11 31
 b.lsbi r11 r11 22
 i.addi r14 r10 -127
 b.seti r13 r11 23
 i64.srai x4 x4 32
 i.sfltsi r14 24
 i64.srli x6 x6 32
 c.bf LBB11_4

 i.addi r11 r10 -150
 i64.srli x5 x5 32
 i64.sll x5 x6 x5
 c.j LBB11_5
LBB11_4:
 i.xori r11 zr 150
 i.sub r11 r11 r10
 i64.srli x5 x5 32
 i64.srl x5 x6 x5
LBB11_5:
 i.xor r13 r11 r9
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 i.xor r12 r10 r8
 i64.sub x4 x6 x4
 c.ret
.tmp11:
 .size __fixsfdi, .tmp11-__fixsfdi

 .globl __floatdisf
 .align 8
 .type __floatdisf,@function
__floatdisf:
.function __floatdisf,Float,Int64

 i.addi sp sp -16
 i.mov r11 zr
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 f.itofmv f8 zr
 i.sd sp 8 x8
 i.sd sp 0 x9
 i64.srli x5 x5 32
 i64.sfeq x4 x5
 c.bf LBB12_11

 i64.srai x5 x4 63
 i.xor r13 r11 r9
 i.xor r12 r10 r8
 i64.sub x4 x6 x5
 i64.srli x6 x4 1
 i.or r15 r9 r13
 i.or r14 r8 r12
 i64.srli x6 x7 2
 i.or r17 r15 r13
 i.or r16 r14 r12
 i64.srli x6 x8 4
 i.or r15 r17 r13
 i.or r14 r16 r12
 i64.srli x6 x7 8
 i.or r17 r15 r13
 i.or r16 r14 r12
 i64.srli x6 x8 16
 i.or r15 r17 r13
 i.or r14 r16 r12
 i64.srli x6 x7 32
 i.or r17 r15 r13
 i.or r16 r14 r12
 i.xori r12 r16 -1
 i.xori r13 r17 -1
 i.movhi r16 21845
 i.ori r16 r16 21845
 i64.srli x7 x6 1
 i.mov r17 r16
 i.and r19 r15 r17
 i.and r18 r14 r16
 i.movhi r14 13107
 i.ori r14 r14 13107
 i64.sub x6 x6 x9
 i.mov r15 r14
 i.and r17 r13 r15
 i.and r16 r12 r14
 i64.srli x6 x6 2
 i.and r19 r13 r15
 i.and r18 r12 r14
 i64.add x6 x8 x9
 i64.srli x7 x6 4
 i64.add x6 x6 x7
 i.movhi r14 3855
 i.ori r14 r14 3855
 i.mov r15 r14
 i.and r17 r13 r15
 i.and r16 r12 r14
 i.movhi r12 257
 i.ori r12 r12 257
 i.mul r13 r16 r12
 i.mulhiu r14 r16 r12
 i.add r13 r14 r13
 i64.srli x7 x8 32
 i.mul r12 r14 r12
 i.add r13 r13 r12
 i64.srli x6 x6 32
 i64.slli x6 x6 32
 i64.srli x7 x6 56
 i.xori r12 zr 64
 i.sub r13 r12 r14
 i.xori r12 zr 63
 i.sub r12 r12 r14
 i.sfltui r13 25
 c.bf LBB12_9

 i.sfeqi r13 26
 c.bnf LBB12_4

 c.j LBB12_7
LBB12_9:
 i.xori r14 zr 24
 i.sub r15 r14 r13
 i64.srli x7 x7 32
 i64.sll x4 x4 x7
 c.j LBB12_10
LBB12_4:
 i.sfnei r13 25
 c.bf LBB12_6

 i64.slli x4 x4 1
 c.j LBB12_7
LBB12_6:
 i.xori r14 zr 90
 i.movhi r16 65535
 i.sub r15 r14 r13
 i.ori r17 r16 65535
 i64.srli x7 x7 32
 i64.srai p0 x8 32
 i64.srl x7 p0 x7
 i.and r17 r15 r9
 i.and r16 r14 r8
 i.mov r15 zr
 i64.srli x9 x7 32
 i64.sfne x8 x9
 i.addi r17 r13 -26
 i.xori r18 zr 1
 i64.srli x8 x8 32
 i64.srl x8 x4 x8
 i.select r9 r18 r15
 i64.srli x7 x4 32
 i.or r9 r15 r17
 i.or r8 r14 r16
LBB12_7:
 i.ori r17 zr 1
 i64.srli x7 x4 2
 i64.srli x8 x8 32
 i.and r19 r15 r17
 i.and r18 r14 r16
 i.or r15 r19 r9
 i.or r14 r18 r8
 i64.addi x4 x7 1
 i.movhi r14 256
 i.ori r15 r14 0
 i64.srai x4 x4 2
 i64.srli x7 x7 32
 i.and r17 r9 r15
 i.and r16 r8 r14
 i.mov r15 zr
 i64.srli x7 x7 32
 i64.sfeq x8 x7
 c.bf LBB12_10

 i64.srli x4 x4 1
 i.mov r12 r13
LBB12_10:
 b.msbi r10 r10 0
 b.lsbi r8 r8 22
 i.slli r11 r12 23
 i.movhi r12 16256
 i.add r9 r11 r12
 i.or r8 r8 r10
 i.or r8 r8 r9
 f.itofmv f8 r8
LBB12_11:
 i.ldd x9 sp 0
 i.ldd x8 sp 8
 i.addi sp sp 16
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp12:
 .size __floatdisf, .tmp12-__floatdisf

 .globl __fixunsdfdi
 .align 8
 .type __fixunsdfdi,@function
__fixunsdfdi:
.function __fixunsdfdi,Int64,Double

 i.addi sp sp -16
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 0 x8
 d.sd sp 8 d4
 i.mov r9 zr
 i.ldd x5 sp 8
 i64.srli x4 x4 32
 i64.srli x7 x5 32
 i.sfltsi r14 0
 c.bnf LBB13_2

 c.j LBB13_7
LBB13_2:
 i64.srli x6 x5 52
 i.andi r12 r12 2047
 i.sfltui r12 1023
 c.bf LBB13_7

 b.lsbi r8 r14 19
 i.addi r13 r12 -1023
 b.seti r9 r8 20
 i.sfltsi r13 53
 i64.srli x4 x4 32
 i64.slli x4 x4 32
 c.bf LBB13_5

 i.movhi r13 65535
 i.ori r15 r13 65535
 i.addi r13 r12 -1075
 i64.srli x7 x7 32
 i.and r17 r11 r15
 i.and r16 r10 r14
 i.or r11 r9 r17
 i.or r10 r8 r16
 i64.srli x4 x6 32
 i64.sll x4 x5 x4
 c.j LBB13_6
LBB13_5:
 i.movhi r13 65535
 i.ori r15 r13 65535
 i.xori r13 zr 1075
 i64.srli x7 x7 32
 i.sub r13 r13 r12
 i.and r17 r11 r15
 i.and r16 r10 r14
 i.or r11 r9 r17
 i.or r10 r8 r16
 i64.srli x4 x6 32
 i64.srl x4 x5 x4
LBB13_6:
 i64.srli x5 x4 32
 i.mov r9 r8
 i.mov r11 r10
 i64.srli x6 x4 32
 i64.srli x5 x5 32
 i64.slli x5 x5 32
 i.or r9 r11 r13
 i.or r8 r10 r12
LBB13_7:
 i.ldd x8 sp 0
 i.addi sp sp 16
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp13:
 .size __fixunsdfdi, .tmp13-__fixunsdfdi

 .globl __fixunssfdi
 .align 8
 .type __fixunssfdi,@function
__fixunssfdi:
.function __fixunssfdi,Int64,Float

 i.mov r9 zr
 f.ftoimv r11 f8
 i64.srli x4 x4 32
 i.sfltsi r11 0
 c.bnf LBB14_2

 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
LBB14_2:
 i.srli r10 r11 23
 i.andi r10 r10 255
 i.sfltui r10 127
 c.bf LBB14_6

 b.lsbi r8 r11 22
 i.addi r12 r10 -127
 b.seti r9 r8 23
 i.sfltsi r12 24
 i64.srli x4 x4 32
 c.bf LBB14_5

 i.addi r11 r10 -150
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 i64.srli x5 x5 32
 i64.sll x4 x4 x5
 c.ret
LBB14_5:
 i.xori r11 zr 150
 i.sub r11 r11 r10
 i64.srli x5 x5 32
 i64.srl x4 x4 x5
LBB14_6:
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp14:
 .size __fixunssfdi, .tmp14-__fixunssfdi

 .globl __floatundisf
 .align 8
 .type __floatundisf,@function
__floatundisf:
.function __floatundisf,Float,Int64

 i.addi sp sp -8
 i.mov r11 zr
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 f.itofmv f8 zr
 i.sd sp 0 x8
 i64.srli x5 x5 32
 i64.sfeq x4 x5
 c.bf LBB15_11

 i64.srli x5 x4 1
 i.or r13 r9 r11
 i.or r12 r8 r10
 i64.srli x5 x6 2
 i.or r15 r13 r11
 i.or r14 r12 r10
 i64.srli x5 x7 4
 i.or r13 r15 r11
 i.or r12 r14 r10
 i64.srli x5 x6 8
 i.or r15 r13 r11
 i.or r14 r12 r10
 i64.srli x5 x7 16
 i.or r13 r15 r11
 i.or r12 r14 r10
 i64.srli x5 x6 32
 i.or r15 r13 r11
 i.or r14 r12 r10
 i.xori r10 r14 -1
 i.xori r11 r15 -1
 i.movhi r14 21845
 i.ori r14 r14 21845
 i64.srli x6 x5 1
 i.mov r15 r14
 i.and r17 r13 r15
 i.and r16 r12 r14
 i.movhi r12 13107
 i.ori r12 r12 13107
 i64.sub x5 x5 x8
 i.mov r13 r12
 i.and r15 r11 r13
 i.and r14 r10 r12
 i64.srli x5 x5 2
 i.and r17 r11 r13
 i.and r16 r10 r12
 i64.add x5 x7 x8
 i64.srli x6 x5 4
 i64.add x5 x5 x6
 i.movhi r12 3855
 i.ori r12 r12 3855
 i.mov r13 r12
 i.and r15 r11 r13
 i.and r14 r10 r12
 i.movhi r10 257
 i.ori r10 r10 257
 i.mul r11 r14 r10
 i.mulhiu r12 r14 r10
 i.add r11 r12 r11
 i64.srli x6 x7 32
 i.mul r10 r12 r10
 i.add r11 r11 r10
 i64.srli x5 x5 32
 i64.slli x5 x5 32
 i64.srli x6 x5 56
 i.xori r10 zr 64
 i.sub r11 r10 r12
 i.xori r10 zr 63
 i.sub r10 r10 r12
 i.sfltui r11 25
 c.bf LBB15_9

 i.sfeqi r11 26
 c.bnf LBB15_4

 c.j LBB15_7
LBB15_9:
 i.xori r12 zr 24
 i.sub r13 r12 r11
 i64.srli x6 x6 32
 i64.sll x4 x4 x6
 c.j LBB15_10
LBB15_4:
 i.sfnei r11 25
 c.bf LBB15_6

 i64.slli x4 x4 1
 c.j LBB15_7
LBB15_6:
 i.xori r12 zr 90
 i.movhi r14 65535
 i.sub r13 r12 r11
 i.ori r15 r14 65535
 i64.srli x6 x6 32
 i64.srai x7 x7 32
 i64.srl x6 x7 x6
 i.and r15 r13 r9
 i.and r14 r12 r8
 i.mov r13 zr
 i64.srli x8 x6 32
 i64.sfne x7 x8
 i.addi r15 r11 -26
 i.xori r16 zr 1
 i64.srli x7 x7 32
 i64.srl x7 x4 x7
 i.select r9 r16 r13
 i64.srli x6 x4 32
 i.or r9 r13 r15
 i.or r8 r12 r14
LBB15_7:
 i.ori r15 zr 1
 i64.srli x6 x4 2
 i64.srli x7 x7 32
 i.and r17 r13 r15
 i.and r16 r12 r14
 i.movhi r14 256
 i.or r13 r17 r9
 i.ori r15 r14 0
 i.or r12 r16 r8
 i64.srli x7 x7 32
 i64.addi x6 x6 1
 i64.srli x4 x6 2
 i.and r17 r9 r15
 i.and r16 r8 r14
 i.mov r15 zr
 i64.srli x7 x7 32
 i64.sfeq x8 x7
 c.bf LBB15_10

 i64.srli x4 x6 3
 i.mov r10 r11
LBB15_10:
 i.slli r10 r10 23
 i.movhi r11 16256
 b.lsbi r8 r8 22
 i.add r10 r10 r11
 i.or r8 r10 r8
 f.itofmv f8 r8
LBB15_11:
 i.ldd x8 sp 0
 i.addi sp sp 8
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp15:
 .size __floatundisf, .tmp15-__floatundisf

 .globl _Z7pzc_AddPfS_S_i
 .align 8
 .type _Z7pzc_AddPfS_S_i,@function
_Z7pzc_AddPfS_S_i:
.function _Z7pzc_AddPfS_S_i,Void,Pointer,Pointer,Pointer,Int32

 i.addi sp sp -8
 i.getpid r15
 i.sflts sp, r4; i.min r5 r5, sp; c.nop ; c.bf exit_stack_error;
 i.sd sp 0 x8
 i.gettid r16
 i.slli r15 r15 3
 i.add r17 r15 r16
 i.sfges r17 r14
 c.bf LBB16_2

 i64.srai x7 x8 32
 i64.slli x7 x7 2
 i64.add p0 x4 x7
 f.eld f2 p0 0
 i64.add p0 x5 x7
 f.eld f3 p0 0
 i64.add p0 x6 x7
 f.add f2 f2 f3
 f.esw p0 0 f2
 c.wflush 8
LBB16_2:
 i.ldd x8 sp 0
 i.addi sp sp 8
 i.ldret lr ; i.movhi zr (((0x01000000)>>16)&0xffff); i.sfgts lr, zr; i.mfspr zr 0x14; c.nop ; c.bf exit_error; c.nop ; i.xor zr zr zr
 c.ret
.tmp16:
 .size _Z7pzc_AddPfS_S_i, .tmp16-_Z7pzc_AddPfS_S_i
