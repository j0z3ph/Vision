// Hello program for Linux x86_64 processor 
// Compilation: 
// nasm -f elf64 hola_linux_x86_64.s -o hola_linux_x86_64.o
// ld hola_linux_x86_64.o -o hello
section .data
    msg db "Holi", 0xa           ; '0xa' is the newline character (\n)
    msg_len equ $ - msg          ; Calculates string length dynamically

section .text
    global _start                ; ELF linker entry point

_start:
    ; 1. sys_write(stdout, msg, msg_len)
    mov rax, 1                   ; System call number for sys_write
    mov rdi, 1                   ; File descriptor 1: stdout
    mov rsi, msg                 ; Pointer to the string
    mov rdx, msg_len             ; Length of the string
    syscall                      ; Invoke the Linux kernel

    ; 2. sys_exit(0)
    mov rax, 60                  ; System call number for sys_exit
    mov rdi, 0                   ; Exit code 0 (Success)
    syscall                      ; Invoke the Linux kernel
