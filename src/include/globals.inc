; copied from S5Hook ;)
; all 999999h values are placeholders

asciiLoaderBase	equ	0AACFA0h
hookBase		equ	22000000h
hookAllocSize	equ 10000h

; free memory: B3FDC0h - B3FFF0
hookAllocdFlag	equ	0B3FDC0h	; byte
hookTempBuf		equ	0B3FDC4h	; unused so far


					; Funcs     ; Args, push order ->
;bluebyte
shok_lua_toint	equ 462384h     ; thiscall: lua state in ecx
shok_eid2obj	equ	51D6D1h
shok_lua_pushint equ 46241Dh    ; thiscall: lua state in ecx
regLuaFunc		equ	465E1Ah		; 0, funcPtr, strFuncName, strTable;   ecx = luaState

;common
strncpy			equ 999999h		; num, src, dest
memcpy 			equ	999999h		; num bytes, source, dest
strlen			equ	999999h		; str, after call len in eax
strdup			equ 999999h
malloc			equ 999999h		


; "global" vars
gloLuaHandle	equ	0AAE09Ch 	; ptr
locLuaHandle	equ 9999999h	; ptr

					;Imports (ptr to funcs)
lua_open		equ	999999h
lua_gettop		equ	999999h
lua_settop		equ	999999h
lua_type		equ	999999h
lua_dostring	equ	999999h
lua_pushstring	equ 999999h
lua_pushnumber	equ 999999h
lua_pushboolean equ	999999h
lua_pushlightuserdata equ 999999h
lua_newtable	equ	999999h
lua_gettable	equ 999999h
lua_settable	equ	999999h
lua_rawget		equ	999999h
lua_rawgeti		equ	999999h
lua_tolstring	equ 8F70CCh		; null/&size, index, luaState
lua_toboolean	equ 999999h
lua_tonumber	equ	999999h
lua_touserdata	equ 999999h
lua_pcall		equ 999999h
luaL_unref		equ	999999h
luaL_ref		equ	999999h
luaL_loadbuffer	equ	8F7090h

lua_tostring	equ 999999h		; does not exist in Lua 5.1

; Windows
virtualAlloc	equ 8F72E0h
virtualQuery	equ	8F732Ch
loadLibraryA	equ	8F7268h
getProcAddress	equ 8F7264h
messageBoxA		equ 8F747Ch



;virtualProtect	equ 999999h		; lpdwOldProtection, dwNewProtection, dwStart, dwLen
; not imported :(

	; constants
LUA_REGISTRYINDEX	equ (-10000)
LUA_ENVIRONINDEX	equ (-10001)
LUA_GLOBALSINDEX	equ (-10002)


%macro  tableEntry	2			; %1 = funcPtr, %2 = string
        dd %1
%%strLeng equ (%%afterStr - %%beforeStr)
		db %%strLeng
%%beforeStr:
		db %2, 0
%%afterStr:

%endmacro