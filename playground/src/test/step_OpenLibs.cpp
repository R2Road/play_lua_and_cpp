#include "pch.h"
#include "step_OpenLibs.h"


//
// http://lua-users.org/wiki/MathLibraryTutorial
//


namespace step
{
	void OpenLibs()
	{
		lua_State* lua_state_obj = luaL_newstate();



		//
		// Command
		//
		const std::string command = "a = math.sin( math.pi * 0.5 )";
		std::cout << "Command : " << command.c_str() << r2::linefeed << r2::linefeed;

		//
		// Test 1
		//
		{
			step_helper::DoString( lua_state_obj, command.c_str() );
		}

		std::cout << r2::linefeed;
		std::cout << "Call : luaL_openlibs" << r2::linefeed;

		luaL_openlibs( lua_state_obj );

		std::cout << r2::linefeed;

		//
		// Test 2
		//
		{
			step_helper::DoString( lua_state_obj, command.c_str() );

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << r2::linefeed;
			}
		}



		lua_close( lua_state_obj );
	}
}
