#include "pch.h"

#include "step_helper.h"
#include "step_PCall_01.h"


namespace step
{
	void PCall_01()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << std::endl;
		luaL_openlibs( lua_state_obj );

		std::cout << std::endl;

		if( !step_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "resources/step_PCall_01.lua" ), "luaL_dofile" ) )
		{
			return;
		}

		std::cout << std::endl;

		//
		// Test x 0
		//
		{
			std::cout << "# Test 0 : Call With Arg x 1" << std::endl;

			lua_getglobal( lua_state_obj, "TestFunction" );
			if( lua_isfunction( lua_state_obj, -1 ) )
			{
				std::cout << "TestFunction is Function" << std::endl;

				lua_pushnumber( lua_state_obj, 123 );

				if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ), "lua_pcall" ) )
				{
					std::cout << "Result : TestFunction : " << static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) << std::endl;
				}
			}
			else
			{
				std::cout << "Is Not Function" << std::endl;
			}
		}

		std::cout << std::endl;

		//
		// Test x 1
		//
		{
			std::cout << "# Test 1 : Call With Arg x 2" << std::endl;

			lua_getglobal( lua_state_obj, "TestFunction" );
			if( lua_isfunction( lua_state_obj, -1 ) )
			{
				std::cout << "TestFunction is Function" << std::endl;

				lua_pushnumber( lua_state_obj, 123 );
				lua_pushnumber( lua_state_obj, 456 );

				if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ), "lua_pcall" ) )
				{
					std::cout << "Result : TestFunction : " << static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) << std::endl;
				}
			}
			else
			{
				std::cout << "Is Not Function" << std::endl;
			}
		}



		lua_close( lua_state_obj );
	}
}
