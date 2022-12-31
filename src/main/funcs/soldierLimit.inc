section luaTable
		tableEntry EMSoldierLimit,   "EMX_SetSoldierLimit"
section code
EMSoldierLimit:
		pushad
			
		mov ecx, dword [listOfEntityIDs]
		push 1
		call 4ABA91h
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError

		mov ecx, [eax + 80h]
		mov ebx, [ecx + 314h]
		
		mov ecx, [esp+24h] ; Lua State
        push 1
        call 462384h ; LuaGetArgument
		
		mov [ebx + 0 * 4h], eax
		mov [ebx + 1 * 4h], eax
		mov [ebx + 2 * 4h], eax
		mov [ebx + 3 * 4h], eax

		mov ecx, [esp+24h] ; get lua state
        push 1		
		jmp returnToLuaState