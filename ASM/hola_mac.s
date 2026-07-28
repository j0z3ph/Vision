// Hello program for MacOS ARM processors 
// Compilation: 
// as -o hola_mac.o hola_mac.s
// ld -o hello hola_mac.o -lSystem -syslibroot $(xcrun -sdk macosx --show-sdk-path) -e _main
.global _main   // Provide program starting address to linker
.align 2   // Make sure everything is aligned properly

// Setup the parameters to print a string
// and then call the Kernel to do it.
_main: 
    mov     X0, #1  // 1 = StdOut
    adr     X1, msg  // string to print
    mov     X2, #5  // length of our string
    mov     X16, #4  // Unix write system call
    svc     #0x80  // Call kernel to output the string

// Setup the parameters to exit the program
// and then call the kernel to do it.
    mov     X0, #0  // Use 0 return code
    mov     X16, #1  // System call number 1 terminates this program
    svc     #0x80  // Call kernel to terminate the program

msg:      
    .ascii  "Holi\n"