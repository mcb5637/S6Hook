section luaTable
        tableEntry EMGetTopMostArchivePath,		"EMX_GetTopMostArchive"
section code
EMGetTopMostArchivePath:
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