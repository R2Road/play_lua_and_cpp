#include "pch.h"

#include "step_helper.h"
#include "step_GetGlobal.h"

namespace step
{
	void GetGlobal()
	{
		lua_State* lua_state_obj = luaL_newstate();


		//
		// Test 1
		//
		{
			std::cout << "lua_getglobal a" << std::endl;

			//
			// Push Variable "a"
			//
			const int type = lua_getglobal( lua_state_obj, "a" );
			step_helper::PrintType( "a", type );
		}

		std::cout << std::endl;

		//
		// Test 2
		//
		{
			const std::string command = "b = 7";
			std::cout << "Command : " << command.c_str() << std::endl;

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

			std::cout << "lua_getglobal b" << std::endl;

			//
			// Push Variable "a"
			//
			const int type = lua_getglobal( lua_state_obj, "b" );
			step_helper::PrintType( "b", type );
		}



		lua_close( lua_state_obj );
	}
}
