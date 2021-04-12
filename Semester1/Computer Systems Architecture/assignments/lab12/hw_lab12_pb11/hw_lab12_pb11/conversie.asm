bits 32

global _conversie

segment data use32 public data
    nr10 dd 0
    zece dw 10
    
segment code use32 public code

_conversie:
    push ebp
    mov ebp, esp    ;stackframe

	mov [nr10], dword 0
	mov eax, 0
    
    mov edx, [ebp + 8]    ;number we have to convert
	mov ecx, [ebp + 12] ; number of digits
    mov ebx, 1      ;power of 2
	mov al, 0
    
    bucla:
        mov al, byte [edx + ecx - 1] ; al = current digit

		cmp al, '1'
		je add_power
		jmp end
        
		add_power:
			add [nr10], ebx
		
		end:
		add ebx, ebx
		loop bucla

final:
mov eax, [nr10]
pop ebp     ;eliminate stackframe
ret 
    