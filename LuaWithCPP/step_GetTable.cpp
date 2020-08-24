#include "pch.h"

#include "step_helper.h"
#include "step_GetTable.h"


void step_GetTable()
{
	lua_State* lua_state_obj = luaL_newstate();



	std::cout << "Call : luaL_openlibs" << std::endl;
	luaL_openlibs( lua_state_obj );

	std::cout << std::endl;

	//
	// Test x 1
	//
	{
		std::cout << "# Test 1" << std::endl;

		if( step_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "Resources/step_GetTable_01.lua" ), "luaL_dofile" ) )
		{
			lua_getglobal( lua_state_obj, "data" );
			if( lua_istable( lua_state_obj, -1 ) )
			{
				std::cout << "data is Table" << std::endl;
				std::cout << std::endl;


				lua_pushstring( lua_state_obj, "name" );
				lua_gettable( lua_state_obj, -2 );
				const std::string name = lua_tostring( lua_state_obj, -1 );
				std::cout << "name : " << name.c_str() << std::endl;
				lua_pop( lua_state_obj, 1 );


				lua_pushstring( lua_state_obj, "age" );
				lua_gettable( lua_state_obj, -2 );
				const int age = lua_tointeger( lua_state_obj, -1 );
				std::cout << "age : " << age << std::endl;
				lua_pop( lua_state_obj, 1 );
			}
			else
			{
				std::cout << "Is Not Table" << std::endl;
			}
		}
	}



	lua_close( lua_state_obj );
}
