section luaTable
        tableEntry getEntityAdress,         "GetEntityAdress"
        tableEntry readFromAdress,          "ReadFromAdress"
        tableEntry writeToAdress,           "WriteToAdress"
section code
getEntityAdress:
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
        
        ; set return value
        push eax
        mov ecx, ebx
        ;push ecx
        call shok_lua_pushint
        
        ; return 1 value
        popad
        mov eax, 1
        retn
readFromAdress:
        pushad
        mov ecx, [esp+24h] ; get lua state
        
        ; get adress
        push 1
        call shok_lua_toint
        mov ebx, eax
        
        ; get offset
        mov ecx, [esp+24h] ; get lua state
        push 2
        call shok_lua_toint
        
        ; read from mem
        mov eax, [ebx+eax*4]
        
        ; push result
        mov ecx, [esp+24h] ; get lua state
        push eax
        call shok_lua_pushint
        
        ; return 1 value
        popad
        mov eax, 1
        retn
writeToAdress:
        pushad
        mov ecx, [esp+24h] ; get lua state
        
        ; get adress
        push 1
        call shok_lua_toint
        ;mov ebx, eax
        push eax
        
        ; get offset
        mov ecx, [esp+28h] ; get lua state
        push 2
        call shok_lua_toint
        ;mov edx, eax
        push eax
        
        ; get value
        mov ecx, [esp+2Ch] ; get lua state
        push 3
        call shok_lua_toint
        
        pop edx
        pop ebx
        ; write to mem
        mov [ebx+edx*4], eax
        
        ; return 0 values
        popad
        mov eax, 0
        retn