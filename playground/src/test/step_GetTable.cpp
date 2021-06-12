#include "pch.h"

#include "step_helper.h"
#include "step_GetTable.h"


namespace step
{
	void GetTable()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << r2::linefeed;
		luaL_openlibs( lua_state_obj );

		std::cout << r2::linefeed;

		//
		// Test x 1
		//
		{
			std::cout << "# Test 1" << r2::linefeed;

			if( step_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "resources/step_GetTable_01.lua" ), "luaL_dofile" ) )
			{
				lua_getglobal( lua_state_obj, "data" );
				if( lua_istable( lua_state_obj, -1 ) )
				{
					std::cout << "data is Table" << r2::linefeed;
					std::cout << r2::linefeed;


					lua_pushstring( lua_state_obj, "name" );
					lua_gettable( lua_state_obj, -2 );
					const std::string name = lua_tostring( lua_state_obj, -1 );
					std::cout << "name : " << name.c_str() << r2::linefeed;
					lua_pop( lua_state_obj, 1 );


					lua_pushstring( lua_state_obj, "age" );
					lua_gettable( lua_state_obj, -2 );
					const int age = (int)lua_tointeger( lua_state_obj, -1 );
					std::cout << "age : " << age << r2::linefeed;
					lua_pop( lua_state_obj, 1 );
				}
				else
				{
					std::cout << "Is Not Table" << r2::linefeed;
				}
			}
		}



		lua_close( lua_state_obj );
	}
}
