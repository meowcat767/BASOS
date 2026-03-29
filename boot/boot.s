.section .multiboot
.align 4
.long 0x1BADB002
.long 0x0
.long -(0x1BADB002)

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.extern kernel_main

_start:
    mov $stack_top, %esp
    
    # Push 0 to mark the end of the stack frame chain
    xor %ebp, %ebp
    push %ebp
    mov %esp, %ebp

    call kernel_main
    cli
hang:
    hlt
    jmp hang