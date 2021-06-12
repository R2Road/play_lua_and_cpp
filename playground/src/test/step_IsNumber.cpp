#include "pch.h"

#include "step_IsNumber.h"

namespace step
{
	void IsNumber()
	{
		lua_State* lua_state_obj = luaL_newstate();



		//
		// Command
		//
		const std::string command = "a = 7 + 11";
		std::cout << "Command : " << command.c_str() << r2::linefeed << r2::linefeed;

		//
		// Do String
		//
		const int result = luaL_dostring( lua_state_obj, command.c_str() );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );
			std::cout << error_message << r2::linefeed;
			return;
		}

		//
		// Push to Stack "a"
		//
		lua_getglobal( lua_state_obj, "a" );

		//
		// Test 1
		//
		{
			std::cout << "lua_tonumber : -1 " << r2::linefeed;

			//
			// -1 : is Last Value Index
			//
			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << r2::linefeed;
			}
		}

		std::cout << r2::linefeed;

		//
		// Test 2
		//
		{
			std::cout << "lua_tonumber : 1 " << r2::linefeed;

			//
			// 1 : is First Stack Index
			//
			if( lua_isnumber( lua_state_obj, 1 ) )
			{
				const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << r2::linefeed;
			}
		}



		lua_close( lua_state_obj );
	}
}
