﻿#include "table_test.h"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace table_test
{
	r2cm::iItem::TitleFunctionT GenerateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Generate";
		};
	}
	r2cm::iItem::DoFunctionT GenerateTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Generate Table" << r2cm::linefeed2;

				PROCESS_MAIN( lua_newtable( lua_state_obj ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				EXPECT_TRUE( lua_istable( lua_state_obj, 1 ) );
			}

			std::cout << r2cm::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2cm::split;


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Add2GlobalTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Add 2 Global";
		};
	}
	r2cm::iItem::DoFunctionT Add2GlobalTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Generate Table" << r2cm::linefeed2;

				PROCESS_MAIN( lua_newtable( lua_state_obj ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Add 2 Global" << r2cm::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get Global" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2cm::split;


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PushAndGetTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 1";
		};
	}
	r2cm::iItem::DoFunctionT PushAndGetTest_1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 1 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2cm::split;


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PushAndGetTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 2";
		};
	}
	r2cm::iItem::DoFunctionT PushAndGetTest_2::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split; 
			
			std::cout << "Note : table을 1이외의 Index에 배치해보기." << r2cm::linefeed;
			
			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PushAndGetTest_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 3 : Invalid Stack Index";
		};
	}
	r2cm::iItem::DoFunctionT PushAndGetTest_3::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			std::cout << "Note : 잘못된 Index에 GetTable 해보기." << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				OUTPUT_CODE( lua_gettable( lua_state_obj, 2 ) );

				std::cout << r2cm::tab << "## Not Working : Invalid Index : Boom" << r2cm::linefeed2;
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PushAndGetTest_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 4 : Invalid Key";
		};
	}
	r2cm::iItem::DoFunctionT PushAndGetTest_4::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			std::cout << "Note : 잘못된 Key로 GetTable 해보기." << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT LuaFunction_And_GetTable::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Lua Function + Get Table";
		};
	}
	r2cm::iItem::DoFunctionT LuaFunction_And_GetTable::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << r2cm::tab << "+ Add Function : GetData( idx )" << r2cm::linefeed2;
			DECLARATION_MAIN( const int arg_count = 1 );
			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/table_test_luafunction_and_gettable_01.lua" ) );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call : GetData( 0 )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "GetData" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 0 ) );
				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Check" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "age" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call : GetData( 1 )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "GetData" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 1 ) );
				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, arg_count, LUA_MULTRET, 0 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Check" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "age" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT GetField::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_getfield";
		};
	}
	r2cm::iItem::DoFunctionT GetField::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* lua_script = "t = { name = 'asdf' }" );
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, lua_script ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "t" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "lua_getfield 를 활용하여 깔끔하게 테이블 내부 데이터 가져오기." );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_getfield( lua_state_obj, -1, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "한 번 더 가져오기." );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_getfield( lua_state_obj, -2, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT SetField::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_setfield";
		};
	}
	r2cm::iItem::DoFunctionT SetField::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* lua_script = "t = {}" );
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, lua_script ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "t" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "lua_setfield 를 활용하여 테이블에 데이터 넣기." );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "asdf" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_setfield( lua_state_obj, -2, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getfield( lua_state_obj, -1, "name" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}