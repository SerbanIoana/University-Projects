bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll


;Read a number in base 16 from the keyboard and display the value 
;of that number in base 10 Example: Read: 1D; display: 29
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format_read db "%x", 0
    ;format_print db "%d", 0
    msg_read db "Number in base 16: ",0
    msg_print db "Number in base 10: %d", 0
    x dd 0

; our code starts here
segment code use32 class=code
    start:
        ;printf(msg_read)
        push msg_read
        call [printf]
        add esp, 4
        
        ;scanf(format_read, &x)
        push dword x
        push format_read
        call [scanf]
        add esp, 4*2
        
        ;printf(msg_print, [x])
        push dword [x]
        push msg_print
        call [printf]
        add esp, 4*2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
