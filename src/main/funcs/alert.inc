section luaTable
		tableEntry showMsgBox,		"Alert"

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