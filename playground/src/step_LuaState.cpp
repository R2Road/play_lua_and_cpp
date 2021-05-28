#include "pch.h"

#include <iostream>

#include "step_LuaState.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
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
