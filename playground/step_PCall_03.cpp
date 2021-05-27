#include "pch.h"

#include "step_helper.h"
#include "step_PCall_03.h"


namespace step
{
	void PCall_03()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << std::endl;
		luaL_openlibs( lua_state_obj );

		std::cout << std::endl;

		if( !step_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "Resources/step_PCall_03.lua" ), "luaL_dofile" ) )
		{
			return;
		}

		std::cout << std::endl;

		lua_getglobal( lua_state_obj, "GetData" );
		std::cout << "lua_getglobal : GetData" << std::endl;

		//
		// Check Stack 1
		//
		step_helper::PrintType( "[Stack 1]", lua_type( lua_state_obj, 1 ) );

		std::cout << std::endl;

		//
		// Test x 0
		//
		if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 0, 1, 0 ), "lua_pcall" ) )
		{
			//
			// Check Stack 1
			//
			step_helper::PrintType( "[Stack 1]", lua_type( lua_state_obj, 1 ) );
		}



		lua_close( lua_state_obj );
	}
}
