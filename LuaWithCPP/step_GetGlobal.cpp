#pragma once

#include "pch.h"

#include "step_GetGlobal.h"

int step_GetGlobal()
{
	lua_State* lua_state_obj = luaL_newstate();


	//
	// Test 1
	//
	{
		//
		// Push Variable "a"
		//
		int result = lua_getglobal( lua_state_obj, "a" );
		if( result != LUA_OK )
		{
			std::cout << "Failed : lua_getglobal : a" << std::endl;

			const auto error_message = lua_tostring( lua_state_obj, -1 );
			std::cout << error_message << std::endl;
		}
		else
		{
			std::cout << "Success : lua_getglobal : a" << std::endl;
			if( lua_isnil( lua_state_obj, -1 ) )
			{
				std::cout << "a is nil" << std::endl;
			}
			else
			{
				std::cout << "a is not nil" << std::endl;
			}
		}
	}



	lua_close( lua_state_obj );

	return 0;
}
