bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)

;Given an array A of doublewords, build two arrays of bytes:  
 ;- array B1 contains as elements the higher part of the higher words from A
 ;- array B2 contains as elements the lower part of the lower words from A

segment data use32 class=data
    a dd 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783A2Bh
    len equ ($-a)/4
    b1 times len db 0
    b2 times len db 0
    

; our code starts here
segment code use32 class=code
    start:
    
        mov esi, s
        mov ebp,b1
        mov edi,b2 
        mov ecx, len
        cld
        
        ;
        repeat:
            lodsd   ;eax<-dword from offset esi
                    ;esi=esi+4
                    ;al<-low part of the low word
                    
            stosb   ;al->byte from offset edi
                    ;edi=edi+1
            shr eax, 16     ;ax=high part of dword
                            ;ah<-high part of the high word
                            
            mov [ebp], ah   ;ah->byte from offset ebp
            inc ebp
            
            loop repeat 
            
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
