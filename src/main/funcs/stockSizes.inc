section luaTable
		tableEntry EMSetMaxStockSize,			"EMX_SetMaxStockSize"
		tableEntry EMGetMaxStockSize,			"EMX_GetMaxStockSize"
		tableEntry EMSetStoreStockSize,			"EMX_SetMaxStoreStockSize"
		tableEntry EMSetMaxBuildingIncome,		"EMX_SetMaxBuildingEarnings"
		tableEntry EMSetFullBuildingCosts,		"EMX_SetFullBuildingCosts"
section code
EMSetFullBuildingCosts:
		pushad
        ; Entity Type as Number
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		
		mov ebx, dword [0AAE060h]
		mov ebx, [ebx + 1Ch]
		mov ebx, dword [ebx + eax * 4h]
		test ebx, ebx ; Is the Object Zero?
		je noObjectFoundError
		
		mov ecx, [esp+24h]
        push 2
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		mov edi, eax
		mov ecx, [esp+24h]
		push 3
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		mov edx, eax
		
		mov ebx, [ebx + 90h]
		test ebx, ebx ; Is the Object Zero?
		je noObjectFoundError
		
		mov [ebx], edi ; Good Type
		mov [ebx + 4h], edx ; Good Amount
		
		mov ecx, [esp+24h]
        push 4
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		mov edi, eax
		mov ecx, [esp+24h]
		push 5
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		mov edx, eax
		
		mov [ebx + 8h], edx ; Good Type
		mov [ebx + 0Ch], edi ; Good Amount
		
		mov ecx, [esp+24h] ; get lua state
        push 1
		jmp returnToLuaState
EMSetMaxBuildingIncome:
		pushad
        ; New Earnings Amount
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		
		mov ebx, dword [playerInformationStruct]
		mov [ebx + 270h], eax

		mov ecx, [esp+24h] ; get lua state
        push 1		
		jmp returnToLuaState
EMSetStoreStockSize:
		pushad
        mov ecx, [esp+24h]
        mov ebx, ecx
		
		; New Stock Size
        push 2
        call shok_lua_toint
		mov ebx, eax
        
        ; Entity ID
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
	       
        ; Entity ID - Ptr Object
        push eax
        call shok_eid2obj
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError

		mov ecx, eax
		call castStockBehavior
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		
		mov ecx, eax
		push ebx ; This is the new Value
		push 1
		call setStockSizeOfObjectStore
		
		mov ecx, [esp+24h] ; get lua state
        push 1		
		jmp returnToLuaState
EMGetMaxStockSize:
        pushad
        mov ecx, [esp+24h] ; get lua state
        mov ebx, ecx
        
        ; get eid
        push 1
        ;push ecx
        call shok_lua_toint
	       
        ; get mem adress
        push eax
        call shok_eid2obj
		test eax, eax
		je noObjectFoundError
        
		mov ecx, eax
		call getOutStockObject
		test eax, eax
		je noObjectFoundError
		
		mov ecx, eax
		push 1 ;useless arg
		call getMaxOutStockSize
		
		mov ecx, [esp+24h] ; get lua state
        push eax
		jmp returnToLuaState
EMSetMaxStockSize:
        pushad
        mov ecx, [esp+24h]
        mov ebx, ecx
		
		; New Stock Size
        push 2
        call shok_lua_toint
		mov ebx, eax
        
        ; Entity ID
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
	       
        ; Entity ID - Ptr Object
        push eax
        call shok_eid2obj
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
        
		mov ecx, eax
		call getOutStockObject
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		
		mov ecx, eax
		push ebx ; This is the new Value
		push 1 ; Useless Argument
		call setMaxOutStockSize
		
		mov ecx, [esp+24h] ; get lua state
        push 1
		jmp returnToLuaState