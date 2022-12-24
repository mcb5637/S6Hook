# S6Hook

S6Hook is a extension for Settlers 6 which can be loaded at runtime through the Lua script embedded in a usermap.

### Usage
Include the code from `output/S6Hook.lua` in your map and execute `InstallS6Hook()`. The return value indicates whether S6Hook was successfully loaded. All functions reside in a global table call `S6Hook`.

### Building
Simply execute the `build.bat` to build the source code into a ready-to-use Lua script.

### Tech
Read more about the implementation [here](https://github.com/Siedelwood/S6Hook/blob/master/TECH.md).