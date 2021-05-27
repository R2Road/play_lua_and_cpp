#include "pch.h"

#include "step_helper.h"
#include "step_PCall_04_CallCPPFunction.h"

void CPPFunctionBody( lua_State* lua_state_obj )
{
	float arg1 = (float)lua_tonumber( lua_state_obj, 1 );
	float arg2 = (float)lua_tonumber( lua_state_obj, 2 );

	std::cout << "Call : CPPFunction : " << arg1 << ", " << arg2 << std::endl;

	const float result = arg1 + arg2;

	lua_pushnumber( lua_state_obj, result );
}

int CPPFunction1( lua_State* lua_state_obj )
{
	CPPFunctionBody( lua_state_obj );
	return 0;
}

int CPPFunction2( lua_State* lua_state_obj )
{
	CPPFunctionBody( lua_state_obj );
	return 1;
}


namespace step
{
	void PCall_04_CallCPPFunction()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << std::endl;
		luaL_openlibs( lua_state_obj );

		std::cout << std::endl << std::endl;

		if( !step_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "Resources/step_PCall_04.lua" ), "luaL_dofile" ) )
		{
			return;
		}

		std::cout << std::endl << std::endl;

		//
		// Test x 0
		//
		{
			std::cout << "# Test 0" << std::endl;
			std::cout << std::endl;

			lua_getglobal( lua_state_obj, "CallCPPFunction1" );
			std::cout << "lua_getglobal : CallCPPFunction1" << std::endl;

			lua_pushnumber( lua_state_obj, 123 );
			lua_pushnumber( lua_state_obj, 456 );

			step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ), "CallCPPFunction1" );
		}

		std::cout << std::endl << std::endl;

		//
		// Test x 1
		//
		{
			std::cout << "# Test 1" << std::endl;
			std::cout << std::endl;

			lua_register( lua_state_obj, "CPPFunction1", CPPFunction1 );
			std::cout << "lua_register : CPPFunction1" << std::endl;
			std::cout << std::endl;

			lua_getglobal( lua_state_obj, "CallCPPFunction1" );
			lua_pushnumber( lua_state_obj, 123 );
			lua_pushnumber( lua_state_obj, 456 );

			if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ), "CallCPPFunction1" ) )
			{
				const int result = (int)lua_tointeger( lua_state_obj, -1 );
				std::cout << "result : " << result << std::endl;
			}
		}

		std::cout << std::endl << std::endl;

		//
		// Test x 2
		//
		{
			std::cout << "# Test 2" << std::endl;
			std::cout << std::endl;

			lua_register( lua_state_obj, "CPPFunction2", CPPFunction2 );
			std::cout << "lua_register : CPPFunction2" << std::endl;
			std::cout << std::endl;

			lua_getglobal( lua_state_obj, "CallCPPFunction2" );
			lua_pushnumber( lua_state_obj, 123 );
			lua_pushnumber( lua_state_obj, 456 );

			if( step_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ), "CallCPPFunction2" ) )
			{
				const int result = (int)lua_tointeger( lua_state_obj, -1 );
				std::cout << "result : " << result << std::endl;
			}
		}



		lua_close( lua_state_obj );
	}
}
