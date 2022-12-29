:: S6Hook buildscript 
:: <2014> yoq
@echo on

:: stage 1 loader
utils\nasm -isrc/include/ -o bin/stage1/asciiPre.bin src/stage1/asciiPre.asm 
utils\nasm -isrc/include/ -o bin/stage1/asciiLoader.bin src/stage1/asciiLoader.asm
utils\alpha2 -n eax < bin/stage1/asciiLoader.bin > bin/stage1/asciiAlpha2.bin
copy /y /b "bin\stage1\asciiPre.bin"+"bin\stage1\asciiAlpha2.bin" "bin\stage1.bin" >nul 
copy /y /b "bin\stage1.bin" "output\stage1.bin" >nul

:: stage 2 loader
utils\nasm -isrc/include/ -o bin/stage2.bin src/stage2/stage2.asm
utils\yoqXpand < bin/stage2.bin > output/stage2.yx

:: main
utils\nasm -isrc/include/ -isrc/main/ -o bin/S6Hook.bin src/main/S6Hook.asm
utils\yoqXpand < bin/S6Hook.bin > output/S6Hook.yx

:: create Lua file
copy /y "src\lua\S6Hook.lua" "output\S6Hook.lua" >nul
utils\yoqTempl "output\S6Hook.lua"
del output\stage1.bin
del output\stage2.yx
del output\S6Hook.yx

pause