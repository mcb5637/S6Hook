section luaTable
		tableEntry EMSoldierLimit,   "EMX_SetSoldierLimit"
		tableEntry EMSetMaxHealth,   "EMX_SetEntityMaxHealth"
section code
EMSetMaxHealth:
		pushad		
        ; Entity ID 
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		
		mov ecx, dword [listOfEntityIDs]
		push eax
		call getEntityIDObjectPtr
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		
		mov edx, dword [eax]
		mov ecx, eax
		;call dword [edx + 0B0h] -> Original Function to get Max Health
		
		mov eax, dword [ecx + 18h]
		mov ecx, dword [00aae060h]
		mov ecx, dword [ecx + 1Ch]
		mov eax, dword [ecx + eax * 4h]
		;mov eax, dword [eax + 24h]
		mov edi, eax 
		
		; New Max Health Value
		mov ecx, [esp+24h]
        push 2
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError

		mov dword [edi + 24h], eax

		mov ecx, [esp+24h] ; get lua state
        push 1
		jmp returnToLuaState
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