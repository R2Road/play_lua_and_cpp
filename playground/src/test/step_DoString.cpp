#include "pch.h"

#include "step_DoString.h"

namespace step
{
	void DoString()
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
			std::cout << "Lua Command : " << command.c_str() << r2::linefeed;

			//
			// Do String
			//
			const int result = luaL_dostring( lua_state_obj, command.c_str() );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "Command Failed " << r2::linefeed;
				std::cout << error_message << r2::linefeed;
			}
			else
			{
				std::cout << "Command Success" << r2::linefeed;
			}
		}

		std::cout << r2::linefeed;


		//
		// Test 2
		//
		{
			//
			// Command x 2
			//
			std::string command = "a = 7 + ";
			std::cout << "Lua Command : " << command.c_str() << r2::linefeed;

			//
			// Do String
			//
			const int result = luaL_dostring( lua_state_obj, command.c_str() );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "Command Failed " << r2::linefeed;
				std::cout << error_message << r2::linefeed;
			}
			else
			{
				std::cout << "Command Success" << r2::linefeed;
			}
		}



		lua_close( lua_state_obj );
	}
}
