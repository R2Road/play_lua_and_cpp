#include "pch.h"
#include "step_PCall_03.h"


namespace step
{
	void PCall_03()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << r2::linefeed;
		luaL_openlibs( lua_state_obj );

		std::cout << r2::linefeed;

		if( !step_helper_deprecated::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "resources/step_PCall_03.lua" ), "luaL_dofile" ) )
		{
			return;
		}

		std::cout << r2::linefeed;

		lua_getglobal( lua_state_obj, "GetData" );
		std::cout << "lua_getglobal : GetData" << r2::linefeed;

		//
		// Check Stack 1
		//
		step_helper_deprecated::PrintType( "[Stack 1]", lua_type( lua_state_obj, 1 ) );

		std::cout << r2::linefeed;

		//
		// Test x 0
		//
		if( step_helper_deprecated::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 0, 1, 0 ), "lua_pcall" ) )
		{
			//
			// Check Stack 1
			//
			step_helper_deprecated::PrintType( "[Stack 1]", lua_type( lua_state_obj, 1 ) );
		}



		lua_close( lua_state_obj );
	}
}
