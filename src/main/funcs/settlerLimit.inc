section luaTable
		tableEntry EMSetterLimit, 			"EMX_SetSettlerLimit"
		tableEntry EMSetterSermonLimit, 	"EMX_SetSermonSettlerLimit"
		tableEntry EMSetTerritoryGoldCost, 	"EMX_SetTerritoryGoldCostByIndex"
section code
EMSetterSermonLimit:
		pushad
		
		mov ecx, dword [listOfEntityIDs]
		push 1
		call 4ABD63h ; Get Object that contains SermonLimitValues
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
				
		mov ebx, dword [eax + 80h]
		mov ebx, [ebx + 2f4h]
		
		mov ecx, [esp+24h] ; Lua State
        push 1
        call 462384h ; LuaGetArgument
	
		mov [ebx + 0 * 4h], eax
		mov [ebx + 1 * 4h], eax
		mov [ebx + 2 * 4h], eax
		mov [ebx + 3 * 4h], eax
		;Again, would it be better to set it by level?

		mov ecx, [esp+24h] ; get lua state
        push 1		
		jmp returnToLuaState
EMSetterLimit:
		pushad
        mov ecx, [esp+24h]

        push 1
        call shok_lua_toint

		mov edx, [playerInformationStruct]
		mov edx, [edx + 198h]
		mov [edx + 0 * 4h], eax
		mov [edx + 1 * 4h], eax
		mov [edx + 2 * 4h], eax
		mov [edx + 3 * 4h], eax
		mov [edx + 4 * 4h], eax
		mov [edx + 5 * 4h], eax
		; TODO - Would it be a better idea to have a Lua arg for the tbl index?
		; Rather than just setting all 6 values to the same size? Don't know 
		
		mov ecx, [esp+24h] ; get lua state
        push 1		
		jmp returnToLuaState
EMSetTerritoryGoldCost:
		pushad
		; New Territory Price
		mov ecx, [esp+24h]
        push 2
        call shok_lua_toint
		test eax, eax ; Is the Object Zero?
		je noObjectFoundError
		mov esi, eax
        ; Territory ID Bracket (0 - 4)
		mov ecx, [esp+24h]
        push 1
        call shok_lua_toint
		; The object here can be zero since it is an array index
		mov ebx, dword [playerInformationStruct]
		cmp eax, 0
		je setIndexZeroInTerritoryArray
		cmp eax, 1
		je setIndexOneInTerritoryArray
		cmp eax, 2
		je setIndexTwoInTerritoryArray
		cmp eax, 3
		je setIndexThreeInTerritoryArray
		cmp eax, 4
		je setIndexFourInTerritoryArray
		jmp noObjectFoundError
		; You have no idea how much i detest this construct :(
setIndexZeroInTerritoryArray:
		mov dword [ebx + 2b0h], dword esi
		jmp jumpOutOfTerritoryFunc
setIndexOneInTerritoryArray:
		mov dword [ebx + 2b4h], dword esi
		jmp jumpOutOfTerritoryFunc
setIndexTwoInTerritoryArray:
		mov dword [ebx + 2b8h], dword esi
		jmp jumpOutOfTerritoryFunc
setIndexThreeInTerritoryArray:
		mov dword [ebx + 700h], dword esi ; WHHHHHHYYYYYYYYY BB ???
		jmp jumpOutOfTerritoryFunc
setIndexFourInTerritoryArray:
		mov dword [ebx + 2c0h], dword esi
jumpOutOfTerritoryFunc:
		mov ecx, [esp+24h] ; get lua state
        push 1
		jmp returnToLuaState