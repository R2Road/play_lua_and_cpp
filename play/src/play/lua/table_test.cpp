#include "table_test.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

namespace table_test
{
	r2tm::TitleFunctionT GenerateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Generate";
		};
	}
	r2tm::DoFunctionT GenerateTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_SUB( lua_State* lua_state_obj = luaL_newstate() );

			LS();

			{
				std::cout << r2tm::tab << "+ Generate Table" << r2tm::linefeed2;

				PROC_MAIN( lua_newtable( lua_state_obj ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( lua_istable( lua_state_obj, 1 ) );
			}

			LS();

			PROC_SUB( lua_close( lua_state_obj ) );

			LS();


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Add2GlobalTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Add 2 Global";
		};
	}
	r2tm::DoFunctionT Add2GlobalTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_SUB( lua_State* lua_state_obj = luaL_newstate() );

			LS();

			{
				std::cout << r2tm::tab << "+ Generate Table" << r2tm::linefeed2;

				PROC_MAIN( lua_newtable( lua_state_obj ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Add 2 Global" << r2tm::linefeed2;

				PROC_MAIN( lua_setglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get Global" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			PROC_SUB( lua_close( lua_state_obj ) );

			LS();


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PushAndGetTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 1";
		};
	}
	r2tm::DoFunctionT PushAndGetTest_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_SUB( lua_State* lua_state_obj = luaL_newstate() );

			LS();

			{
				PROC_MAIN( lua_newtable( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Ready" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Push" << r2tm::linefeed2;

				PROC_MAIN( lua_settable( lua_state_obj, 1 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 1 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			PROC_SUB( lua_close( lua_state_obj ) );

			LS();


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PushAndGetTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 2";
		};
	}
	r2tm::DoFunctionT PushAndGetTest_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS(); 
			
			std::cout << "Note : table을 1이외의 Index에 배치해보기." << r2tm::linefeed;
			
			LS();

			{
				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_newtable( lua_state_obj ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Push" << r2tm::linefeed2;

				PROC_MAIN( lua_settable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PushAndGetTest_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 3 : Invalid Stack Index";
		};
	}
	r2tm::DoFunctionT PushAndGetTest_3::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			std::cout << "Note : 잘못된 Index에 GetTable 해보기." << r2tm::linefeed;

			LS();

			{
				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_newtable( lua_state_obj ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Push" << r2tm::linefeed2;

				PROC_MAIN( lua_settable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				OUT_CODE( lua_gettable( lua_state_obj, 2 ) );

				std::cout << r2tm::tab << "## Not Working : Invalid Index : Boom" << r2tm::linefeed2;
			}

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PushAndGetTest_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 4 : Invalid Key";
		};
	}
	r2tm::DoFunctionT PushAndGetTest_4::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			std::cout << "Note : 잘못된 Key로 GetTable 해보기." << r2tm::linefeed;

			LS();

			{
				PROC_MAIN( lua_newtable( lua_state_obj ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Push" << r2tm::linefeed2;

				PROC_MAIN( lua_settable( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT LuaFunction_And_GetTable::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Lua Function + Get Table";
		};
	}
	r2tm::DoFunctionT LuaFunction_And_GetTable::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			LS();

			std::cout << r2tm::tab << "+ Add Function : GetData( idx )" << r2tm::linefeed2;
			DECL_MAIN( const int arg_count = 1 );
			PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/table_test_luafunction_and_gettable_01.lua" ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Call : GetData( 0 )" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "GetData" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 0 ) );
				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Check" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "age" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 1 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call : GetData( 1 )" << r2tm::linefeed2;

				PROC_MAIN( lua_settop( lua_state_obj, 0 ) );

				PROC_MAIN( lua_getglobal( lua_state_obj, "GetData" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 1 ) );
				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Check" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "age" ) );
				PROC_MAIN( lua_gettable( lua_state_obj, 1 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT GetField::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_getfield";
		};
	}
	r2tm::DoFunctionT GetField::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			{
				DECL_MAIN( const char* lua_script = "t = { name = 'asdf' }" );
				PROC_MAIN( test_lua_helper::DoString( lua_state_obj, lua_script ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( lua_state_obj, "t" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				OUT_NOTE( "lua_getfield 를 활용하여 깔끔하게 테이블 내부 데이터 가져오기." );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_getfield( lua_state_obj, -1, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				OUT_NOTE( "한 번 더 가져오기." );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_getfield( lua_state_obj, -2, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT SetField::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_setfield";
		};
	}
	r2tm::DoFunctionT SetField::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			{
				DECL_MAIN( const char* lua_script = "t = {}" );
				PROC_MAIN( test_lua_helper::DoString( lua_state_obj, lua_script ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( lua_state_obj, "t" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				OUT_NOTE( "lua_setfield 를 활용하여 테이블에 데이터 넣기." );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushstring( lua_state_obj, "asdf" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_setfield( lua_state_obj, -2, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				PROC_MAIN( lua_getfield( lua_state_obj, -1, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}