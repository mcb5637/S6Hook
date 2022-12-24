bits 32
%include 'globals.inc'

org hookBase
jmp		installer				; entry point after stage2

	; const strings
section strings align=1
sS6Hook			db "S6Hook", 0

section luaTable align=1
luaFuncTable:
		tableEntry triggerInt3,		"Break"

section globalVars align=1
				dd 0						; 0 marks end of table
											; no global vars so far
				
section code align=1
installer:
		pushad 
		mov edi, [gloLuaHandle]
		mov esi, luaFuncTable	
.nextEntry:
		push 0						; no description
		push dword [esi]			; func ptr
		add esi, 5
		push esi					; func name (string)
		movzx eax, byte [esi-1]		; skip over func name
		add esi, eax
		push sS6Hook				; base table
		mov ecx, edi				; global lua_state
		call regLuaFunc
		
		cmp dword [esi], 0
		jnz .nextEntry
		
		; TODO: insert hooks to call unpatchEverything 
		; on unload of the map (see S5Hook) 
		
		popad
		retn
		
%include 'funcs/baseFunctions.inc'
%include 'funcs/memoryManipulation.inc'
%include 'funcs/stockSizes.inc'
%include 'funcs/settlerLimit.inc'
%include 'funcs/archiveLoading.inc'

triggerInt3:
		int3
		xor eax, eax
		retn
		
		; TODO: code for these hooks 

unpatchEverything:
section cleanup align=1
		retn