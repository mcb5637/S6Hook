; all 999999h values are placeholders
asciiLoaderBase	equ	0AACFA0h
hookBase		equ	22000000h
hookAllocSize	equ 10000h

; free memory: B3FDC0h - B3FFF0
hookAllocdFlag	equ	0B3FDC0h	; byte
hookTempBuf		equ	0B3FDC4h	; unused so far

; Funcs     ; Args, push order ->
;bluebyte

shok_lua_toint	        equ 462384h     ; thiscall: lua state in ecx
shok_eid2obj	        equ	51D6D1h
shok_lua_pushint        equ 46241Dh    ; thiscall: lua state in ecx
regLuaFunc		        equ	465E1Ah		; 0, funcPtr, strFuncName, strTable;   ecx = luaState

;Added By Eisenmonoxid
setStockSizeOfObjectStore equ 5c2df3h 
;setStorehouseStock       equ 5c2c83h ; useless :(
getAmountOfOutStock       equ 5ba9b0h 
getOutStockObject         equ 4f3fdeh
getMaxOutStockSize        equ 50c6a0h
setMaxOutStockSize        equ 50d353h 
castStockBehavior         equ 4f403ch

getSettlerLimit           equ 4fd91fh
getOffsetOfObject         equ 667f28h
listOfEntityIDs           equ 0aae400h ; ptr to global object

dynamicCast               equ 72aa63h
playerInformationStruct   equ 0aae0fch ; ptr to global object

;Stuff for Archive Loading
addBBAArchive             equ 63d26dh
getStringValue            equ 5fc63ah
fileSystemManager         equ 0aaba5ch

;fileSystemMgr - stuff
fileSystemMgr_MAKEPTHABS  equ 30h ;TEST + 4 - Probably not needed anyway
fileSystemMgr_LOADARCHIVE equ 1Ch ;Here, we know the new value
fileSystemMgr_STARTPTR    equ 8 ;Shifted by 1 bit to the left
fileSystemMgr_FILENAME    equ 0Ch ;Same as S5

shok_FileSystemMgrVtO_RemoveTopArchive  equ 2Ch ; Not really sure right now ...

;common
strncpy			equ 999999h		; num, src, dest
memcpy 			equ	999999h		; num bytes, source, dest
strlen			equ	999999h		; str, after call len in eax
strdup			equ 999999h
malloc			equ 999999h		

; "global" vars
gloLuaHandle	equ	0AAE09Ch 	; ptr to object
locLuaHandle	equ 0AAE058h	; ptr to object

;Imports (ptr to funcs)
lua_open		equ	999999h
lua_gettop		equ	999999h
lua_settop		equ	999999h
lua_type		equ	999999h
lua_dostring	equ	999999h
lua_pushstring	equ 462447h ; this, str
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