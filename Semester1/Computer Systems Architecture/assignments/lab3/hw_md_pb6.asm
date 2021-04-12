bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;x+a/b+c*d-b/c+e; a,b,d-byte; c-word; e-doubleword; x-qword

segment data use32 class=data
    a db 3
    b db 2
    c dw 5
    d db 4
    e dd 7
    x dq 3
    t dd 0

; our code starts here
segment code use32 class=code
    start:
        
        mov al, [a]
        cbw     ;ax=a
        
        idiv byte [b]   ;al=a/b ;ah=a%b 
        
        cbw
        cwde
        cdq     ;edx:eax=a/b
        
        add [x], eax
        adc [x+4], edx  ;x=x+a/b
        
        mov al, [d]
        cbw     ;ax=d
        
        imul word [c]    ;dx:ax=c*d
        
        mov [t], ax
        mov [t+2], dx   ;t=c*d
        
        mov eax, [t]    ;eax=c*d
        cdq         ;edx:eax=c*d
        
        add [x], eax
        adc [x+4], edx      ;x=x+a/b+c*d
        
        mov al, [b]
        cbw
        cwd     ;dx:ax=b
        
        idiv word [c]   ;ax=b/c     ;dx=b%c
        
        cwde
        cdq     ;edx:eax=b/c
        
        sub [x], eax
        sbb [x+4], edx    ;x=x+a/b+c*d-b/c
        
        mov eax, [e]
        cdq     ;edx:eax=e 
        
        add [x], eax
        adc [x+4], edx      ;x=x+a/b+c*d-b/c+e
        
        mov eax, [x]
        mov edx, [x+4]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
