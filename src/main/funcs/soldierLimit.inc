section luaTable
		tableEntry EMSoldierLimit,   "EMX_SetSoldierLimit"
		tableEntry EMSetMaxHealth,   "EMX_SetEntityMaxHealth"
section code
EMSetMaxHealth:
		pushad		
		
        ; entity ID 
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		
		mov ecx, dword [listOfEntityIDs]
		push eax
		call getEntityIDObjectPtr
		test eax, eax
		je noObjectFoundError
		
		mov edx, dword [eax]
		mov ecx, eax
		;call dword [edx + 0B0h] -> original function to get max health
		
		mov eax, dword [ecx + 18h]
		mov ecx, dword [00aae060h]
		mov ecx, dword [ecx + 1Ch]
		mov eax, dword [ecx + eax * 4h]
		test eax, eax
		je noObjectFoundError
		
		mov edi, eax 
		
		; get the new max health value
		mov ecx, [esp+24h]
        push 2
        call shok_lua_toint
		test eax, eax ; value can't be zero
		je noObjectFoundError

		mov dword [edi + 24h], dword eax

		mov ecx, [esp+24h]
        push 1
		jmp returnToLuaState
EMSoldierLimit:
		pushad
			
		mov ecx, dword [listOfEntityIDs]
		push 1
		call 4ABA91h
		test eax, eax
		je noObjectFoundError

		mov ecx, [eax + 80h]
		mov ebx, [ecx + 314h]
		
		mov ecx, [esp+24h]
        push 1
        call 462384h ; get lua arg
	
		xor ecx, ecx
	.loopSoldierLimit:
		mov [ebx + ecx * 4h], eax
		inc ecx
		cmp ecx, 3
		jle .loopSoldierLimit

		mov ecx, [esp+24h]
        push 1		
		jmp returnToLuaState