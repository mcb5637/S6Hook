section luaTable
		tableEntry showMsgBox,		"Alert"
		tableEntry evalLua, 		"Eval"
section strings
		sAlertCapt	db "S6Hook Info", 0
section code
showMsgBox:
		mov esi, [esp+4]		; lua state
		
		push 0					; dont get the length of the string
		push 1					; first lua arg
		push esi
		call [lua_tolstring]
		add esp, 12
		
		push 40h				; MB_OK | MB_ICONEXCLAMATION
		push sAlertCapt			; caption
		push eax				; text
		push 0					; window handle, optional
		call [messageBoxA]
		
		xor eax, eax
		retn
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
returnToLuaState:
		call shok_lua_pushint
		popad
		mov eax, 1 ; Return whether it worked or not
        retn
noObjectFoundError:
		mov ecx, [esp+24h] ; get lua state
        push 0		
		jmp returnToLuaState