#pragma once

#include "pch.h"

#include "step_OpenLibs.h"


//
// http://lua-users.org/wiki/MathLibraryTutorial
//


void step_OpenLibs()
{
	lua_State* lua_state_obj = luaL_newstate();



	//
	// Command
	//
	const std::string command = "a = math.sin( math.pi * 0.5 )";
	std::cout << "Command : " << command.c_str() << std::endl << std::endl;

	//
	// Test 1
	//
	{
		const int result = luaL_dostring( lua_state_obj, command.c_str() );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "Command Failed " << std::endl;
			std::cout << error_message << std::endl;
		}
		else
		{
			std::cout << "Command Success" << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "Call : luaL_openlibs" << std::endl;

	luaL_openlibs( lua_state_obj );

	std::cout << std::endl;

	//
	// Test 2
	//
	{
		const int result = luaL_dostring( lua_state_obj, command.c_str() );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "Command Failed " << std::endl;
			std::cout << error_message << std::endl;
		}
		else
		{
			std::cout << "Command Success" << std::endl;
		}

		lua_getglobal( lua_state_obj, "a" );

		if( lua_isnumber( lua_state_obj, -1 ) )
		{
			const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
			std::cout << "result : " << "a : " << a << std::endl;
		}
	}



	lua_close( lua_state_obj );
}
