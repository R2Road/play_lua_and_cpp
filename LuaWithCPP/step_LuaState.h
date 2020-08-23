#include "pch.h"
#include <iostream>

extern "C"
{
#include "Lua54/include/lua.h"
#include "Lua54/include/lauxlib.h"
#include "Lua54/include/lualib.h"
}

int step_LuaState()
{
	//
	// Make Lua State
	//
	lua_State* lua_state_obj = luaL_newstate();

	//
	// Current Command
	//
	const std::string command = "a = 7 + 11";
	std::cout << "lua command : " << command.c_str() << std::endl;

	//
	// Do Command
	//
	const int result = luaL_dostring( lua_state_obj, command.c_str() );
	if( result != LUA_OK )
	{
		const auto error_message = lua_tostring( lua_state_obj, -1 );
		std::cout << error_message << std::endl;
	}

	//
	// Get
	//
	lua_getglobal( lua_state_obj, "a" );
	if( lua_isnumber( lua_state_obj, -1 ) )
	{
		const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
		std::cout << "result : " << "a : " << a << std::endl;
	}
	
	//
	// End
	//
	lua_close( lua_state_obj );

	return 0;
}
