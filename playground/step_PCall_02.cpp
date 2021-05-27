#include "pch.h"

#include "step_helper.h"
#include "step_PCall_02.h"


namespace step
{
	void PCall_02()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << std::endl;
		luaL_openlibs( lua_state_obj );

		std::cout << std::endl;

		if( !step_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "Resources/step_PCall_02.lua" ), "luaL_dofile" ) )
		{
			return;
		}

		std::cout << std::endl;

		lua_getglobal( lua_state_obj, "GetData" );
		if( lua_isfunction( lua_state_obj, -1 ) )
		{
			std::cout << "GetData is Function" << std::endl;
		}
		else
		{
			std::cout << "GetData is Not Function" << std::endl;
		}

		std::cout << std::endl;

		//
		// Test x 0
		//
		{
			std::cout << "# Test 0" << std::endl;

			lua_pushnumber( lua_state_obj, 0 );

			if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 1, 1, 0 ), "lua_pcall" ) )
			{
				lua_pushstring( lua_state_obj, "name" );
				lua_gettable( lua_state_obj, -2 );
				const std::string name = lua_tostring( lua_state_obj, -1 );
				std::cout << "name : " << name.c_str() << std::endl;
				lua_pop( lua_state_obj, 1 );


				lua_pushstring( lua_state_obj, "age" );
				lua_gettable( lua_state_obj, -2 );
				const int age = (int)lua_tointeger( lua_state_obj, -1 );
				std::cout << "age : " << age << std::endl;
				lua_pop( lua_state_obj, 1 );
			}

		}

		std::cout << std::endl;
		lua_getglobal( lua_state_obj, "GetData" );

		//
		// Test x 1
		//
		{
			std::cout << "# Test 1" << std::endl;

			lua_pushnumber( lua_state_obj, 1 );

			if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 1, 1, 0 ), "lua_pcall" ) )
			{
				lua_pushstring( lua_state_obj, "name" );
				lua_gettable( lua_state_obj, -2 );
				const std::string name = lua_tostring( lua_state_obj, -1 );
				std::cout << "name : " << name.c_str() << std::endl;
				lua_pop( lua_state_obj, 1 );


				lua_pushstring( lua_state_obj, "age" );
				lua_gettable( lua_state_obj, -2 );
				const int age = (int)lua_tointeger( lua_state_obj, -1 );
				std::cout << "age : " << age << std::endl;
				lua_pop( lua_state_obj, 1 );
			}

		}



		lua_close( lua_state_obj );
	}
}
