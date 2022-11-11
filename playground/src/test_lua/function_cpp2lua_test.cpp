#include "pch.h"
#include "function_cpp2lua_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

namespace function_cpp2lua_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << r2cm::tab << "+ Add Function : Test()" << r2cm::linefeed2;

			SHOW_FILE( "resources/function_cpp2lua_test_basic_01.lua" );

			std::cout << r2cm::linefeed;

			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_cpp2lua_test_basic_01.lua" ) );
			DECLARATION_MAIN( const int argument_count = 0 );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready : lua 전역 공간에서 함수를 가져와 스택에 넣는다." << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Test" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				EXPECT_TRUE( lua_isfunction( lua_state_obj, 1 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call" << r2cm::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, argument_count, LUA_MULTRET, 0 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Argument2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Argument 2";
		};
	}
	r2cm::iItem::DoFunctionT Argument2::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << r2cm::tab << "+ Add Function : Sum( arg1, arg2 )" << r2cm::linefeed2;
			DECLARATION_MAIN( const int arg_count = 2 );
			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_cpp2lua_test_01.lua" ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready : 인자 1개 부족" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call : 인자 1개 부족" << r2cm::linefeed2;

				EXPECT_EQ( LUA_ERRRUN, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintLuaError( lua_state_obj );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 456 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call" << r2cm::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
