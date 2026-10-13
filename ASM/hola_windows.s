// Hello program for Windows x86_64 processor 
// Compilation: 
// nasm -f win64 hola_windows.s -o hola_windows.obj
// gcc hola_windows.obj -o hola
default rel
bits 64

; Import necessary functions from kernel32.dll
extern GetStdHandle
extern WriteFile
extern ExitProcess

section .data
    message  db "Holi", 13, 10      ; 13, 10 represents a CR/LF newline
    msg_len  equ $ - message

section .bss
    bytes_written resq 1    ; Reserve space to store the number of bytes actually written

section .text
global main
main:
    ; --- Windows x64 Calling Convention Setup ---
    ; Allocate 40 bytes of stack space:
    ; - 32 bytes for shadow space (required by the Windows ABI)
    ; - 8 bytes to keep the stack 16-byte aligned
    sub rsp, 40

    ; --- Step 1: Get Handle to stdout ---
    ; GetStdHandle standard handle constant for stdout is -11 (STD_OUT)
    mov rcx, -11            ; Argument 1 (rcx): nStdHandle = STD_OUTPUT_HANDLE
    call GetStdHandle       ; RAX will hold the returned handle
    
    ; --- Step 2: Write to the Console ---
    ; WriteFile parameters: (handle, buffer, length, &bytesWritten, reserved)
    mov rcx, rax            ; Argument 1 (rcx): hFile (the stdout handle)
    lea rdx, [message]      ; Argument 2 (rdx): lpBuffer (pointer to message)
    mov r8d, msg_len        ; Argument 3 (r8d): nNumberOfBytesToWrite
    lea r9, [bytes_written] ; Argument 4 (r9): lpNumberOfBytesWritten
    mov qword [rsp + 32], 0 ; Argument 5 (Stack): lpOverlapped = NULL

    call WriteFile

    ; --- Step 3: Exit cleanly ---
    xor rcx, rcx            ; Argument 1 (rcx): uExitCode = 0
    call ExitProcess
