#include "pch.h"
#include "table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace table_test
{
	r2cm::iItem::TitleFuncT GenerateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Generate";
		};
	}
	r2cm::iItem::DoFuncT GenerateTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Generate Table" << r2::linefeed2;

				PROCESS_MAIN( lua_newtable( lua_state_obj ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				EXPECT_TRUE( lua_istable( lua_state_obj, 1 ) );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Add2GlobalTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Add 2 Global";
		};
	}
	r2cm::iItem::DoFuncT Add2GlobalTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Generate Table" << r2::linefeed2;

				PROCESS_MAIN( lua_newtable( lua_state_obj ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Add 2 Global" << r2::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get Global" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PushAndGetTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 1";
		};
	}
	r2cm::iItem::DoFuncT PushAndGetTest_1::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push" << r2::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 1 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PushAndGetTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 2";
		};
	}
	r2cm::iItem::DoFuncT PushAndGetTest_2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split; 
			
			std::cout << "Note : table을 1이외의 Index에 배치해보기." << r2::linefeed;
			
			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push" << r2::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PushAndGetTest_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 3 : Invalid Stack Index";
		};
	}
	r2cm::iItem::DoFuncT PushAndGetTest_3::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			std::cout << "Note : 잘못된 Index에 GetTable 해보기." << r2::linefeed;

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push" << r2::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 3 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				SHOW_CODE( lua_gettable( lua_state_obj, 2 ) );

				std::cout << r2::tab << "## Not Working : Invalid Index : Boom" << r2::linefeed2;
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PushAndGetTest_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push And Get Value 4 : Invalid Key";
		};
	}
	r2cm::iItem::DoFuncT PushAndGetTest_4::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			std::cout << "Note : 잘못된 Key로 GetTable 해보기." << r2::linefeed;

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push" << r2::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT LuaFunction_And_GetTable::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Lua Function + Get Table";
		};
	}
	r2cm::iItem::DoFuncT LuaFunction_And_GetTable::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << r2::tab << "+ Add Function : GetData( idx )" << r2::linefeed2;
			DECLARATION_MAIN( const int arg_count = 1 );
			PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/table_test_luafunction_and_gettable_01.lua" ) );

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