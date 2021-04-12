bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;Given the byte A and the word B, compute the byte C as follows:
;1. the bits 0-3 are the same as the bits 2-5 of A
;2. the bits 4-7 are the same as the bits 6-9 of B.

segment data use32 class=data
    a db 1010 1011b
    b dw 0101 1101 0110 0110b
    c db 0

; our code starts here
segment code use32 class=code
    start:
        mov cl, 0
        
        ;1
        mov al, [a]
        and al, 0011 1100b      ;isolate bits 2-5
        shr al, 2   ;bits 2-5 will now be at 0-3
        or cl, al
        
        ;2
        mov bx, [b]
        and bx, 0000 0011 1100 0000b    ;isolate bits 6-9
        shr bx, 2   ;bits 6-9 -> 4-7
        or cl,bl
        
        mov [c], cl 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
