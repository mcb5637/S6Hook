section luaTable
		tableEntry EMSetMaxStockSize,		"EMX_SetMaxStockSize"
		tableEntry EMGetMaxStockSize,		"EMX_GetMaxStockSize"
		tableEntry EMSetStoreStockSize,		"EMX_SetMaxStoreStockSize"
section code
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

		mov ecx, eax
		call castStockBehavior
		
		mov dword [eax + 4ch], ebx

        popad
		mov eax, 0
        retn
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
        
		mov ecx, eax
		call getOutStockObject
		
		mov ecx, eax
		push 1 ;useless arg
		call getMaxOutStockSize
		
		mov ecx, [esp+24h] ; get lua state
        push eax
        call shok_lua_pushint

        ; return 1 value
        popad
        mov eax, 1
        retn
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
	       
        ; Entity ID -> Ptr Object
        push eax
        call shok_eid2obj
        
		; Ptr - Object -> Cast to OutStockObject
		mov ecx, eax
		call getOutStockObject
		
		; Set the new Value in the corresponding array index 
		mov dword [eax + 34h], ebx

        popad
		mov eax, 0
        retn