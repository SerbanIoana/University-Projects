bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;[2*(a+b)-5*c]*(d-3)

segment data use32 class=data
    a db 2
    b db 4
    c db 2
    d dw 5

; our code starts here
; [2*(a+b)-5*c]*(d-3)
segment code use32 class=code
    start:
        
        
        mov al, [a] ;al=a
        add al, [b] ;al=a+b
        
        mov bl, 2   ;bl=2
        mul bl  ;ax=2*(a+b)
        
        mov cx, ax  ;cx=2*(a+b)
        
        mov al, 5   ;al=5
        mul byte [c]    ;ax=5*c
        
        sub cx, ax  ;cx=2*(a+b)-5*c
        mov ax, cx  ;ax=2*(a+b)-5*c
        
        mov bx, [d] ;bx=d
        sub bx, 3   ;bx=d-3
        
        mul bx  ;dx:ax=[2*(a+b)-5*c]*(d-3)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
