#include "pch.h"
#include "function_lua2cpp_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

void CPPFunctionBody( lua_State* lua_state_obj )
{
	float arg1 = (float)lua_tonumber( lua_state_obj, 1 );
	float arg2 = (float)lua_tonumber( lua_state_obj, 2 );

	std::cout << "Call : CPPFunction : " << arg1 << ", " << arg2 << r2::linefeed;

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


namespace function_lua2cpp_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return " function_lua2cpp_test : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << "Call : luaL_openlibs" << r2::linefeed;
				luaL_openlibs( lua_state_obj );

				std::cout << r2::linefeed << r2::linefeed;

				if( !test_lua_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "resources/step_PCall_04.lua" ) ) )
				{
					//return;
				}

				std::cout << r2::linefeed << r2::linefeed;

				//
				// Test x 0
				//
				{
					std::cout << "# Test 0" << r2::linefeed;
					std::cout << r2::linefeed;

					lua_getglobal( lua_state_obj, "CallCPPFunction1" );
					std::cout << "lua_getglobal : CallCPPFunction1" << r2::linefeed;

					lua_pushnumber( lua_state_obj, 123 );
					lua_pushnumber( lua_state_obj, 456 );

					test_lua_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ) );
				}

				std::cout << r2::linefeed << r2::linefeed;

				//
				// Test x 1
				//
				{
					std::cout << "# Test 1" << r2::linefeed;
					std::cout << r2::linefeed;

					lua_register( lua_state_obj, "CPPFunction1", CPPFunction1 );
					std::cout << "lua_register : CPPFunction1" << r2::linefeed;
					std::cout << r2::linefeed;

					lua_getglobal( lua_state_obj, "CallCPPFunction1" );
					lua_pushnumber( lua_state_obj, 123 );
					lua_pushnumber( lua_state_obj, 456 );

					if( test_lua_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ) ) )
					{
						const int result = (int)lua_tointeger( lua_state_obj, -1 );
						std::cout << "result : " << result << r2::linefeed;
					}
				}

				std::cout << r2::linefeed << r2::linefeed;

				//
				// Test x 2
				//
				{
					std::cout << "# Test 2" << r2::linefeed;
					std::cout << r2::linefeed;

					lua_register( lua_state_obj, "CPPFunction2", CPPFunction2 );
					std::cout << "lua_register : CPPFunction2" << r2::linefeed;
					std::cout << r2::linefeed;

					lua_getglobal( lua_state_obj, "CallCPPFunction2" );
					lua_pushnumber( lua_state_obj, 123 );
					lua_pushnumber( lua_state_obj, 456 );

					if( test_lua_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ) ) )
					{
						const int result = (int)lua_tointeger( lua_state_obj, -1 );
						std::cout << "result : " << result << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}
}
