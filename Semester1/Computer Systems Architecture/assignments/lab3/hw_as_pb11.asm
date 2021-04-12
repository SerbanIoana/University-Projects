bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;(d-c)+(b-a)-(b+b+b)

segment data use32 class=data
    a db 2
    b dw 4
    c dd 1
    d dq 5
    t dq 0
; our code starts here
segment code use32 class=code
    start:
        ;c dd -> dq
        mov eax, [c]
        cdq     ;edx:eax=c 
        
        mov ebx, [d]
        sub ebx, eax
        
        mov ecx, [d+4]
        sbb ecx, edx    ;ecx:ebx=d-c
        
        mov [t], ebx
        mov [t+4], ecx  ;t=d-c 
        
        mov al, [a]     ;al=a 
        cbw     ;ax=a
        
        mov bx, [b]
        sub bx, ax  ;bx=b-a
        
        mov ax, bx
        cwde    ;eax=b-a 
        cdq     ;edx:eax=b-a
        
        add [t], eax
        adc [t+4], edx  ;t=(d-c)+(b-a)
        
        mov ax, [b]
        add ax, [b]
        add ax, [b]     ;ax=b+b+b
        
        cwde
        cdq     ;edx:eax=b+b+b
        
        sub [t], eax
        sbb [t+4], edx
        
        mov eax, [t]
        mov edx, [t+4]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
