#adesalu
#kafisher
#lrbloch
﻿       .file   "hello.c"
        .section        .rodata
        .align  2
.LC0:
        .ascii  "Hello World! \n"
        .ascii "Goodbye World! \000"
        # \000 indicates EOF, so move it to end of 
        # goodbye phrase and insert newline between
        .text
        .align  2
        .global main
        .type   main, %function
main:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 0
        @ frame_needed = 1, uses_anonymous_args = 0
        mov     ip, sp
        stmfd   sp!, {fp, ip, lr, pc}
        sub     fp, ip, #4
        ldr     r0, .L3
        bl      puts
        mov     r3, #42  @stores exit status in r3
        mov     r0, r3
        sub     sp, fp, #12
        ldmfd   sp, {fp, sp, lr}
        bx      lr
.L4:
        .align  2
.L3:
        .word   .LC0
        .size   main, .-main
        .ident  "GCC: (GNU) 4.1.2"
