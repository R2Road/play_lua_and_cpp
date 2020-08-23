#pragma once

#include "pch.h"

#include "step_DoString.h"

int step_DoString()
{
	lua_State* lua_state_obj = luaL_newstate();


	std::string command;

	//
	// Test 1
	//
	{
		//
		// Command x 1
		//
		command = "a = 7 + 11";
		std::cout << "Lua Command : " << command.c_str() << std::endl;

		//
		// Do String
		//
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


	//
	// Test 2
	//
	{
		//
		// Command x 2
		//
		std::string command = "a = 7 + ";
		std::cout << "Lua Command : " << command.c_str() << std::endl;

		//
		// Do String
		//
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



	lua_close( lua_state_obj );

	return 0;
}
