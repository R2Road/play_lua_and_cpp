#include "pch.h"
#include "function_cpp2lua_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace function_cpp2lua_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << r2::tab << "+ Add Function" << r2::linefeed2;
			DECLARATION_MAIN( const int argument_count = 0 );
			DECLARATION_MAIN( const char* command_arg0_function = "function Test() print( 'Call : TestFunction()' ) end" );
			PROCESS_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, command_arg0_function ) );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready : lua 전역 공간에서 함수를 가져와 스택에 넣는다." << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Test" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				EXPECT_TRUE( lua_isfunction( lua_state_obj, 1 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call" << r2::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, argument_count, LUA_MULTRET, 0 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Argument2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Argument 2";
		};
	}
	r2cm::iItem::DoFuncT Argument2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << r2::tab << "+ Add Function : Sum( arg1, arg2 )" << r2::linefeed2;
			DECLARATION_MAIN( const int arg_count = 2 );
			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/function_cpp2lua_test_01.lua" ) );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready : 인자 1개 부족" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call : 인자 1개 부족" << r2::linefeed2;

				EXPECT_EQ( LUA_ERRRUN, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintLuaError( lua_state_obj );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "Sum" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 456 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call" << r2::linefeed2;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT GetTable::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua : Get Table";
		};
	}
	r2cm::iItem::DoFuncT GetTable::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << r2::tab << "+ Add Function : GetData( idx )" << r2::linefeed2;
			DECLARATION_MAIN( const int arg_count = 1 );
			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/step_PCall_02.lua" ) );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "GetData" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 0 ) );
				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Check" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "age" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call" << r2::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "GetData" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 1 ) );
				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Check" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "age" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
