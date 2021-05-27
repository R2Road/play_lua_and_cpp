#include "pch.h"

#include <iostream>

#include "step_LuaState.h"

extern "C"
{
#include "../Lua54/include/lua.h"
#include "../Lua54/include/lauxlib.h"
#include "../Lua54/include/lualib.h"
}

namespace step
{
	void LuaState()
	{
		//
		// Make Lua State
		//
		lua_State* lua_state_obj = luaL_newstate();
		std::cout << "Make lua_State" << std::endl;

		//
		// End
		//
		lua_close( lua_state_obj );
		std::cout << "Close lua_State" << std::endl;
	}
}
