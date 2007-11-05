
#include <stdio.h>
#include <string.h>
#include <lua/lua.hpp>

#include <string>

#include <DataBlock.h>
using namespace IO;

int main(int argc, char* argv[]) {
	if ( argc <= 1 ) {
		fprintf(stderr, "Usage: LuaTest <LuaProgram.lua>");
		return 1;
	}

	lua_State *L = lua_open();   /* opens Lua */
	luaL_openlibs(L); /* replaces LUA 5.0 default library commands */
	
	{
		cDataBlock Buffer( argv[1] );
	
		std::string FileName = "Object: ";
		FileName += argv[1];
	
		// luaL_loadbuffer( LUA Handle, string data, size in bytes, name to refer to as in errors )
		// lua_pcall - Call what's on the stack.  Has specific options, but 0,0,0 is easy. 
	
		bool Error = luaL_loadbuffer(L, Buffer.Data(), Buffer.Size(), FileName.c_str()) || lua_pcall(L, 0, 0, 0);
		
		if (Error) {
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);  /* pop error message from the stack */
		}
	}

	
	lua_close(L);
	return 0;
}
