#include "function_lua2cpp_test.h"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

int CPPFunction_0( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPFunction_0" << r2cm::linefeed;

	return 0;
}

int CPPFunction_1( lua_State* lua_state_obj )
{
	float arg1 = (float)lua_tonumber( lua_state_obj, 1 );

	std::cout << "[CPP] START : " << arg1 << r2cm::linefeed;

	lua_pushnumber( lua_state_obj, arg1 * 0.01 );
	lua_pushnumber( lua_state_obj, arg1 * 0.1 );

	return 2; // 반환값 숫자
}

int CPPFunction_2( lua_State* lua_state_obj )
{
	float arg1 = (float)lua_tonumber( lua_state_obj, 1 );
	float arg2 = (float)lua_tonumber( lua_state_obj, 2 );

	std::cout << "[CPP] START : " << arg1 << ", " << arg2 << r2cm::linefeed;

	const float result = arg1 + arg2;

	lua_pushnumber( lua_state_obj, result * 0.01 );
	lua_pushnumber( lua_state_obj, result * 0.1 );
	lua_pushnumber( lua_state_obj, result );

	return 3; // 반환값 숫자
}


namespace function_lua2cpp_test
{
	r2cm::iItem::TitleFunctionT Register_And_PCall::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Register And PCall";
		};
	}
	r2cm::iItem::DoFunctionT Register_And_PCall::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			OUTPUT_NOTE( "cpp 펑션의 반환값 0 = 반환값 없음" );
			OUTPUT_NOTE( "cpp 펑션의 반환값 n = 반환값의 수, 스택에 값을 넣어두면 반환값으로 처리" );

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/function_lua2cpp_test_register_n_pcall_01.lua" );
				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_lua2cpp_test_register_n_pcall_01.lua" ) );
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



	r2cm::iItem::TitleFunctionT Argument::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Argument";
		};
	}
	r2cm::iItem::DoFunctionT Argument::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_lua2cpp_test_argument_01.lua" ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Return Arg x 1" << r2cm::linefeed2;

				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_1", CPPFunction_1 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "LUAFunction_1" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pcall( lua_state_obj, 1, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Return Arg x 3" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_register( lua_state_obj, "CPPFunction_2", CPPFunction_2 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "LUAFunction_2" ) );
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



	r2cm::iItem::TitleFunctionT Lambda::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_lua2cpp_test : Lambda";
		};
	}
	r2cm::iItem::DoFunctionT Lambda::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/function_lua2cpp_test_lambda_01.lua" );
				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_lua2cpp_test_lambda_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "Lambda 함수 등록" );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto cpp_func = []( lua_State* l )->int
				{
					std::cout << "[CPP] Start\n";
					lua_pushnumber( l, 7 );
					std::cout << "[CPP] End\n";

					return 1;
				} );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, cpp_func ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPFunction" ) );
			}

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "Call" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "LUAFunction" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pcall( lua_state_obj, 0, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
