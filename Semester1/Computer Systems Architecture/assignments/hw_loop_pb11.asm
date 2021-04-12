bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;A byte string S is given. Obtain the string D1 which contains all the even numbers of S 
;and the string D2 which contains all the odd numbers of S
;S: 1, 5, 3, 8, 2, 9
;D1: 8, 2
;D2: 1, 5, 3, 9

segment data use32 class=data
    s db 1,5,3,8,2,9
    len equ $-s
    d1 times len db 0
    d2 times len db 0

; our code starts here
segment code use32 class=code
    start:
        
        mov esi, s
        mov edi,d1
        mov ebp,d2 
        mov ecx, len
        
        cld
        
        repeat:
            mov al, [esi]   ;al<-byte from offset esi
            
            test al, 1   ;test if al is even or odd
                        ;if ZF=1 => even number
                        ;else => odd number
            jz even_number   ;zf=1
            
            ;to do if number is odd 
            mov [ebp], al   ;al->byte from offset ebp
            inc ebp
            
            even_number:
                mov [edi], al   ;al->byte from offset edi
                inc edi
            
            dec ecx
            
            loop repeat     ;dec ecx
                            ;cmp ecx, 0
                            ;jnz repeat
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
