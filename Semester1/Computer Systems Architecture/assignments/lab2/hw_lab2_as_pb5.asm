bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2
    b db 3
    c db 10
    d db 5

; our code starts here

;(c-a-d)+(c-b)-a

segment code use32 class=code
    start:
        
        mov al, [c] ;ax=c
        sub al, [a] ;ax=c-a
        sub al, [d] ;ax=c-a-d
        
        mov bl, [c] ;bx=c
        sub bl, [b] ;bx=c-b
        
        add al, bl  ;ax=(c-a-d)+(c-b)
        sub al, [a] ;ax=(c-a-d)+(c-b)-a
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
