#include "pch.h"
#include "table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace lua_table_test
{
	r2cm::iItem::TitleFuncT GenerateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Table : Generate";
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

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );

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
			return "Table : Add 2 Global";
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

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Add 2 Global" << r2::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get Global" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "dummy_table" ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Table : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );
			DECLARATION_SUB( luaL_openlibs( lua_state_obj ) );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Load Table" << r2::linefeed2;

				PROCESS_MAIN( test_lua_helper::DoFile( lua_state_obj, "resources/step_GetTable_01.lua" ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "data" ) );
				EXPECT_TRUE( lua_istable( lua_state_obj, 1 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PushAndGetTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Table : Push And Get Value";
		};
	}
	r2cm::iItem::DoFuncT PushAndGetTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_newtable( lua_state_obj ) );
				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push" << r2::linefeed2;

				PROCESS_MAIN( lua_settable( lua_state_obj, 1 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_int" ) );
				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}
}