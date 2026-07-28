// Hello program for Linux ARM processor 
// Compilation: 
// as -o hola_linux.o hola_linux.s
// ld -o hello hola_linux.o
.global _start   // Provide program starting address to linker
.align 2   // Make sure everything is aligned properly

.section .text

// Setup the parameters to print a string
// and then call the Kernel to do it.
_start:
    mov     X0, #1  // 1 = StdOut
    adr     X1, msg  // string to print
    mov     X2, #5  // length of our string
    mov     X8, #64  // system call number for sys_write
    svc     #0  // Call kernel to output the string

// Setup the parameters to exit the program
// and then call the kernel to do it.
    mov     X0, #0  // Use 0 return code
    mov     X8, #93  // System call number for sys_exit
    svc     #0  // Call kernel to terminate the program

msg:
    .ascii  "Holi\n"
