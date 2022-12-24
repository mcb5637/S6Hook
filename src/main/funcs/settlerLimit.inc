section luaTable
		tableEntry EMSetterLimit, 			"EMX_SetSettlerLimit"
		;tableEntry EMSetterSermonLimit, 	"EMX_SetSermonSettlerLimit"
section code
EMSetterSermonLimit:
		pushad
        mov ecx, [esp+24h]
        mov ebx, ecx
		
        push 1
        call shok_lua_toint

		mov edx, [playerInformationStruct]
		mov edx, [edx + 198h]
		mov eax, [edx + eax * 4h]

		mov ecx, [esp+24h] ; get lua state
        push eax
        call 46241dh ;Write Double to Lua
		
        popad
		mov eax, 1 ; 1 Return Values to Lua State
        retn
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
		
        popad
		mov eax, 0 ; 0 Return Values to Lua State
        retn