#adesalu
#lrbloch
#kafisher
﻿       .file   "part1-strTable.c"
        .text
        .align  2
        .global strTable
        .type   strTable, %function
strTable:
        #removed all 'mov' statements, unnecessary
        @ args = 0, pretend = 0, frame = 0
        @ frame_needed = 0, uses_anonymous_args = 0
        subs    r2, r3, #1      @ r2 = length of dst string - 1
        ble     .L11            @ if r2 <= 0, return
.L9:
        ldrb    ip, [r1, r2]    @ zero_extendqisi2; ip = letter in dst to write to src
        mov     r4, ip          @ store ip in a local reg so you can mess w/it
.L10:
        # for loop: decrements r4 (orig'ly ip)
        # by 23 until it is the index
        # of a letter in src to replace
        sub     r4, r4, #23
        cmp     r4, #22
        bgt     .L10
.L13:
        ldrb    r3, [r0, r4]    @ zero_extendqisi2
        cmp     r3, ip          @ dst letter == src letter?
        strneb  ip, [r0, r4]    @ if not equal overwrite src letter w/dest letter
.L4:
        subs    r2, r2, #1      @ r2 (count), decrements from 7 to 0
        bpl     .L9             @ if 0, done!
.L11:
        #restore context and leave
        mov pc, lr
        .size   strTable, .-strTable
        .ident  "GCC: (GNU) 3.4.5"
