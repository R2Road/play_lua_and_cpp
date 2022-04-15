#include "pch.h"
#include "function_lua2cpp_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

int CPPFunction_0( lua_State* lua_state_obj )
{
	std::cout << "[CPP] Call : CPPFunction_0" << r2::linefeed;

	return 0;
}

void CPPFunctionBody( lua_State* lua_state_obj )
{
	float arg1 = (float)lua_tonumber( lua_state_obj, 1 );
	float arg2 = (float)lua_tonumber( lua_state_obj, 2 );

	std::cout << "[CPP] Call : CPPFunction : " << arg1 << ", " << arg2 << r2::linefeed;

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
	r2cm::iItem::TitleFuncT Basic_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Basic 1";
		};
	}
	r2cm::iItem::DoFuncT Basic_1::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << "Note : cpp 펑션의 반환값 0 = 반환값 없음" << r2::linefeed;
			std::cout << "Note : cpp 펑션의 반환값 n = 반환값의 수, 스택에 값을 넣어두면 반환값으로 처리" << r2::linefeed;

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const char* command = "function LUAFunction_0()    CPPFunction_0()    end"; )
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Register Cpp Function" << r2::linefeed2;

				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_0", CPPFunction_0 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call Lua Function" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "LUAFunction_0" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Basic_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Basic 2";
		};
	}
	r2cm::iItem::DoFuncT Basic_2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_lua2cpp_test_01.lua" ) );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Return Arg x 1" << r2::linefeed2;

				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_1", CPPFunction_1 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPFunction_1" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 456 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				PROCESS_MAIN( lua_pcall( lua_state_obj, 2, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Return Arg x 3" << r2::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_2", CPPFunction_2 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPFunction_2" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 234 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 567 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				PROCESS_MAIN( lua_pcall( lua_state_obj, 2, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;
			


			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}
}
