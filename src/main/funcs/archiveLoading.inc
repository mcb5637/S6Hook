section luaTable
        tableEntry getTopMostArchivePath,   "EMX_GetTopMostArchive"
		;tableEntry loadArchive,   "EMX_LoadArchive" ;Next Revision
section code
getTopMostArchivePath:
        pushad
		mov ecx, [esp+24h] ; get lua state
        mov ebx, ecx
        
        mov dword esi, [fileSystemManager]
        mov eax, [esi + fileSystemMgr_STARTPTR]
        mov eax, [eax]
        mov eax, [eax + fileSystemMgr_FILENAME]
		
		push eax
        mov ecx, ebx
		call lua_pushstring

        popad
        mov eax, 1; 1 return values to lua
        retn
loadArchive:
        pushad
        mov ebx, [esp + 24h] ; lua state in ebx
        
        sub esp, 100h ;"allocate" stack size
        mov ebp, esp
        
		push 0
        push 1
        push ebx
        call [lua_tolstring]
		;file string is now in eax
		
		;.loadArchive
		mov dword esi, [fileSystemManager]
        mov eax, [esi + fileSystemMgr_STARTPTR]
        mov eax, [eax]
        mov eax, [eax + fileSystemMgr_FILENAME]
		;int1
		push 605e90c5h              ; WHAT THE ... ???
		push 1                      ; at top flag
        push eax                    ; filename
        
        mov dword ecx, [fileSystemManager]
        mov edx, [ecx]
        call [edx + fileSystemMgr_LOADARCHIVE]              ; loadArchive
        
        add esp, 100h ; "free" stack memory
        popad
        xor eax, eax
        retn