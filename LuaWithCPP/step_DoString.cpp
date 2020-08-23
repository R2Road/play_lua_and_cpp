#pragma once

#include "pch.h"

int step_DoString()
{
	lua_State* lua_state_obj = luaL_newstate();

	//
	// Current Command
	//
	const std::string command = "a = 7 + 11";
	std::cout << "lua command : " << command.c_str() << std::endl;

	//
	// Do String
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

	//
	// -1 : is last value
	//
	if( lua_isnumber( lua_state_obj, -1 ) )
	{
		const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
		std::cout << "result : " << "a : " << a << std::endl;
	}

	//
	// 1
	//
	if( lua_isnumber( lua_state_obj, 1 ) )
	{
		const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
		std::cout << "result : " << "a : " << a << std::endl;
	}

	lua_close( lua_state_obj );

	return 0;
}
