bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


;A file name is given (defined in the data segment). 
;Create a file with the given name, then read words from the keyboard 
;and write those words in the file, until character '$' is read from the keyboard.

segment data use32 class=data
    file_name db "a.txt",0
    access_mode db "w",0
    file_handle dd 0
    w times 100 db 0
    format db "%s", 0
    format_print db "%s ", 0
    msg_read db "x= ", 0

; our code starts here
segment code use32 class=code
    start:
        ;fopen(file_name, access_mode)
        push access_mode
        push file_name
        call [fopen]
        add esp, 4*2
        
        ;file handle in eax
        mov [file_handle], eax
        
        cmp eax, 0
        je final
        
        repeat_loop:
            ;printf("x= ")
            push msg_read
            call [printf]
            add esp, 4
            
            ;scanf("%s", &x)
            push w 
            push format
            call [scanf]
            add esp, 4*2
            
            cmp byte [w], '$'
            je final
            
            ;pusha
            ;fprintf(file_handle, format_print, [x])
            push w 
            push format_print
            push dword [file_handle]
            call [fprintf]
            add esp, 4*3
            
            jmp repeat_loop
    
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
