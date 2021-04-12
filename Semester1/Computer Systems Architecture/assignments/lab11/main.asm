bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

import printf msvcrt.dll
import scanf msvcrt.dll

extern transformare


;Multiple numbers in base 2 are read from the keyboard. Display these numbers in the base 16.
segment data use32 class=data
    n db 0
    msgread db "n = ", 0
    format db "%d", 0
    formatprint db "%x", 0

; our code starts here
segment code use32 class=code
    start:
        
        bucla:
            ;printf(msgread)
            push msgread
            call [printf]
            add esp, 4
            
            ;scanf(format, &n)
            push n
            push format
            call [scanf]
            add esp, 4*2
            
            cmp byte [n], '$'
            je final
            
            ;transformare(n)
            push dword [n]
            call transformare
            
            ;printf(formatprint,eax)
            push eax
            push formatprint
            call [printf]
            add esp, 4*2
            
            jmp bucla
            
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
