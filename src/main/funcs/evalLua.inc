section luaTable
		tableEntry evalLua, 		"Eval"

section code
evalLua:
		mov esi, [esp+4]			; retrieve lua_state ptr
		
		push eax					; dummy, space for size variable
		mov ebp, esp				; ptr to size var
		
		push ebp					; ptr to size var
		push 1						; first lua arg
		push esi					; lua state
		call [lua_tolstring]
									; string is now in eax
		
		push 0						; no name for code block
		push dword [ebp]			; size
		push eax					; the lua code from arg1
		push esi					; lua state
		call [luaL_loadbuffer]
		
		add esp, 32					; clean stack
		
		mov eax, 1					; loadbuffer has already pushed the function 
									; on the return stack, so we return 1
									; to indicate that there is 1 return value
		retn