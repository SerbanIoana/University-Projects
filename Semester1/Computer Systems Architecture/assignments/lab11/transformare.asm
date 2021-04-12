bits 32

global transformare

segment data use32 public data
    nr10 dd 0
    zece dw 10
    
segment code use32 public code

transformare:
    push ebp
    mov ebp, esp    ;stackframe
    mov eax, 0
    mov eax, [ebp+8]    ;number we have to convert
    mov ebx, 1      ;power of 2
    
    bucla:
        cmp eax, 0
        je final
        
        push eax
        pop ax
        pop dx
        
        idiv word [zece]     ;ax = eax/10, dx = eax%10
        cwde        ;eax = eax/10
        
        cmp dx, 0
        je next
        
        add [nr10], ebx     ;only if dx (last digit) is 1
        
        next:
            mov ecx, ebx
            add ebx, ecx   ;powers of 2
           
        jmp bucla
        
    final:
    mov eax, [nr10]
    pop ebp     ;eliminate stackframe
    ret 4
    