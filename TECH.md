## Overview
### Inital Loader [stage1]
Is executed directly in the Log buffer and can only contain 
printable characters (``32 <= c <= 127``).
This loads ``stage2`` from the 2nd Lua argument and jumps to
the first instruction of ``stage2``

### 2nd Stage Loader [stage2]
Allocates memory for S6Hook and copies it from the 3rd 
Lua argument to the newly allocated memory region
It also makes the ``.text`` section writeable.
Then it calls the installer of the main S6Hook binary

### The main S6Hook binary [main]
Holds all extension functions and also contains an installer
to register all functions in the appropriate Lua state.

# 
## Executing the Extension Code

A entity is presumably laid out in memory like this:
```
class Entity
{
	void *vtable_pointer;	// normally invisible, the compiler creates this member
	[...]
	int entityID;
	[...]
	int scriptingValues[2];
	[...]
	float entityScale;
	[...]
}
```
The main vulnerability are these two functions:
 - `Logic.GetEntityScriptingValue(eID, nr)`
 - `Logic.SetEntityScriptingValue(eID, nr, value)`
 
These two Lua functions allow unchecked(!) access to the RAM,
albeit relative from a random location in the heap.

````
Entity::SetScriptingValue(int nr, int value)
{
	//no bounds checking occurs (!)
	this->scriptingValues[nr] = value;
}
````
Because we don't know where the entity object is located on the heap, we cannot 
access any absolute address using this facility.
But it is possible to modify the vtable pointer using a negative value 
for the ScriptingValue nr. In Settlers 6 (patch 1.71) this is ``-81``.

So we need a function that allows us to place (more-or-less) arbitrary data
in a buffer with a fixed address in memory. Here another Settlers API function
becomes useful: ``Framework.WriteToLog(string text)``.
This function writes all text to a fixed buffer (1024byte) before writing it
into the logfile. This buffer is located at ``0x00AACFA0`` in memory but there is
a significant restriction: Only printable characters are allowed.

This is circumvented by encoding the stage1 loader code using ALPHA2.
A small piece of ASCII-assembly needs to be handwritten to place the baseaddress
of the loader code into eax.

Then all there is left to do is modify the ``vtable_pointer`` so that a virtual call
is rerouted to our code in the log buffer.
We use ``entity->Destroy()``, or as seen from Lua: ``Logic.DestroyEntity(eId)``
To pass the code for the stage2 loader and the main S6Hook binary, we can use the fact
that Lua can not check for uneccessary arguments and pass these two binarys as the 2nd and 3rd
arguments to the ``DestroyEntity()`` function. Then in the loader code this is retrieved using 
``lua_tolstring(lua_State *L, int argNr, int *strLen)``. Because Lua treats strings as binary buffers, we don't have any restrictions on the code.