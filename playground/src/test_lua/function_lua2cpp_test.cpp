#include "pch.h"
#include "function_lua2cpp_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

int CPPFunction_0( lua_State* lua_state_obj )
{
	std::cout << "[CPP] Call : CPPFunction_0" << r2cm::linefeed;

	return 0;
}

void CPPFunctionBody( lua_State* lua_state_obj )
{
	float arg1 = (float)lua_tonumber( lua_state_obj, 1 );
	float arg2 = (float)lua_tonumber( lua_state_obj, 2 );

	std::cout << "[CPP] Call : CPPFunction : " << arg1 << ", " << arg2 << r2cm::linefeed;

	const float result = arg1 + arg2;

	lua_pushnumber( lua_state_obj, result * 0.01 );
	lua_pushnumber( lua_state_obj, result * 0.1 );
	lua_pushnumber( lua_state_obj, result );
}

int CPPFunction_1( lua_State* lua_state_obj )
{
	CPPFunctionBody( lua_state_obj );
	return 1;
}

int CPPFunction_2( lua_State* lua_state_obj )
{
	CPPFunctionBody( lua_state_obj );
	return 3;
}


namespace function_lua2cpp_test
{
	r2cm::iItem::TitleFunctionT Basic_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Basic 1";
		};
	}
	r2cm::iItem::DoFunctionT Basic_1::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << "Note : cpp 펑션의 반환값 0 = 반환값 없음" << r2cm::linefeed;
			std::cout << "Note : cpp 펑션의 반환값 n = 반환값의 수, 스택에 값을 넣어두면 반환값으로 처리" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* command = "function LUAFunction_0()    CPPFunction_0()    end"; )
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Register Cpp Function" << r2cm::linefeed2;

				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_0", CPPFunction_0 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call Lua Function" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "LUAFunction_0" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Basic_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Basic 2";
		};
	}
	r2cm::iItem::DoFunctionT Basic_2::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_lua2cpp_test_01.lua" ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Return Arg x 1" << r2cm::linefeed2;

				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_1", CPPFunction_1 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPFunction_1" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 456 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pcall( lua_state_obj, 2, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Return Arg x 3" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_2", CPPFunction_2 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPFunction_2" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 234 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 567 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pcall( lua_state_obj, 2, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;
			


			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
