section luaTable
		tableEntry EMSetMaxStockSize,			"EMX_SetMaxStockSize"
		tableEntry EMGetMaxStockSize,			"EMX_GetMaxStockSize"
		tableEntry EMSetStoreStockSize,			"EMX_SetMaxStoreStockSize"
		tableEntry EMSetMaxBuildingIncome,		"EMX_SetMaxBuildingEarnings"
		tableEntry EMSetFullBuildingCosts,		"EMX_SetFullBuildingCosts"
		tableEntry EMSetOutStockGoodOfBuilding, "EMX_SetOutStockGoodBuildingID"
section code
EMSetOutStockGoodOfBuilding:
		pushad
	
		mov ecx, [esp + 24h]
        push 1
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		
		push eax
        call shok_eid2obj
		test eax, eax
		je noObjectFoundError
		
		mov ecx, eax
		call 4f3fdeh
		mov ebx, eax
		
		mov ecx, [esp + 24h]
        push 2
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		
		mov ebx, dword [ebx + 18h]	
		mov dword [ebx], eax
		
		mov ecx, [esp+24h]
        push 1
		jmp returnToLuaState
EMSetFullBuildingCosts:
		pushad
		
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		
		mov ebx, dword [0AAE060h]
		mov ebx, [ebx + 1Ch]
		mov ebx, dword [ebx + eax * 4h]
		
		mov ecx, [esp+24h]
        push 2
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError

		mov edi, eax
		mov ecx, [esp+24h]
		push 3
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		mov edx, eax
		
		mov ebx, [ebx + 90h]		
		mov [ebx], edi ; good type
		mov [ebx + 4h], edx ; good amount
		
		mov ecx, [esp+24h]
        push 4
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError ; when the building only has one good, exit here
		
		mov edi, eax
		mov ecx, [esp+24h]
		push 5
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		
		mov edx, eax
		mov [ebx + 8h], edx ; good type
		mov [ebx + 0Ch], edi ; good amount
		
		mov ecx, [esp+24h]
        push 1
		jmp returnToLuaState
EMSetMaxBuildingIncome:
		pushad
		
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		
		mov ebx, dword [playerInformationStruct]
		mov dword [ebx + 270h], eax

		mov ecx, [esp+24h]
        push 1		
		jmp returnToLuaState
EMSetStoreStockSize:
		pushad
		
        mov ecx, [esp+24h]
        push 2
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		mov ebx, eax

		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError

        push eax
        call shok_eid2obj
		test eax, eax
		je noObjectFoundError

		mov ecx, eax
		call castStockBehavior
		
		mov dword [eax + 4Ch], dword ebx 
		
		mov ecx, [esp+24h]
        push 1		
		jmp returnToLuaState
EMGetMaxStockSize:
        pushad
		
        mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
	       
        push eax
        call shok_eid2obj
		test eax, eax
		je noObjectFoundError

		mov ecx, eax
		call getOutStockObject
		
		mov eax, dword [eax + 34h]
		
		mov ecx, [esp+24h]
        push eax
		jmp returnToLuaState
EMSetMaxStockSize:
        pushad
		
        mov ecx, [esp+24h]	
        push 2
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
		mov ebx, eax
        
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax
		je noObjectFoundError
	       
        push eax
        call shok_eid2obj
		test eax, eax
		je noObjectFoundError
        
		mov ecx, eax
		call getOutStockObject
		
		mov dword [eax + 34h], dword ebx
				
		mov ecx, [esp+24h]
        push 1
		jmp returnToLuaState