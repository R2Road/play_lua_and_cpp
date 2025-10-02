#include "function_cpp2lua_test.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

namespace function_cpp2lua_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			LS();

			std::cout << r2tm::tab << "+ Add Function : Test()" << r2tm::linefeed2;

			OUT_FILE( "resources/function_cpp2lua_test_basic_01.lua" );

			LF();

			PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_cpp2lua_test_basic_01.lua" ) );
			DECL_MAIN( const int argument_count = 0 );

			LS();

			{
				std::cout << r2tm::tab << "+ Ready : lua 전역 공간에서 함수를 가져와 스택에 넣는다." << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "Test" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				LF();

				EXPECT_TRUE( lua_isfunction( lua_state_obj, 1 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call" << r2tm::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, argument_count, LUA_MULTRET, 0 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Argument::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Argument";
		};
	}
	r2tm::DoFunctionT Argument::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			LS();

			std::cout << r2tm::tab << "+ Add Function : Sum( arg1, arg2 )" << r2tm::linefeed2;
			DECL_MAIN( const int arg_count = 2 );
			PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_cpp2lua_test_argument_01.lua" ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Ready : 인자 1개 부족" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call : 인자 1개 부족" << r2tm::linefeed2;

				EXPECT_EQ( LUA_ERRRUN, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				LF();

				test_lua_helper::PrintLuaError( lua_state_obj );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Ready" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 456 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call" << r2tm::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}
}
