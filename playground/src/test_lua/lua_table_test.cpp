#include "pch.h"
#include "lua_table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace lua_table_test
{
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



	r2cm::iItem::TitleFuncT GetTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Table : Get";
		};
	}
	r2cm::iItem::DoFuncT GetTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );
			DECLARATION_SUB( luaL_openlibs( lua_state_obj ) );

			std::cout << r2::split;

			PROCESS_MAIN( test_lua_helper::DoFile( lua_state_obj, "resources/step_GetTable_01.lua" ) );

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "data" ) );
				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "name" ) );
				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );

				std::cout << r2::linefeed;
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_gettable( lua_state_obj, 1 ) );
				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( lua_pop( lua_state_obj, 1 ) );
			}

			std::cout << r2::split;

			{
				lua_pushstring( lua_state_obj, "age" );
				lua_gettable( lua_state_obj, -2 );
				const int age = (int)lua_tointeger( lua_state_obj, -1 );
				std::cout << "age : " << age << r2::linefeed;
				lua_pop( lua_state_obj, 1 );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}
}