#include "pch.h"
#include "lua_type_check_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"
#include "test_lua_helper.h"

namespace lua_type_check_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Check : lua_getglobal, lua_type, lua_isnumber...";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 0 : Stack Empty" << r2::linefeed2;

				DECLARATION_MAIN( const int type = lua_type( lua_state_obj, 1 ) );
				PROCESS_MAIN( test_lua_helper::PrintTypeName( type ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, "a = 7 + 11" ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 1 : Get Type With Push 2 Stack" << r2::linefeed2;

				DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "a" ) );
				PROCESS_MAIN( test_lua_helper::PrintTypeName( type ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 2 : Get Type In Stack" << r2::linefeed2;
				
				DECLARATION_MAIN( const int type = lua_type( lua_state_obj, 1 ) );
				PROCESS_MAIN( test_lua_helper::PrintTypeName( type ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 3 : Type Check In Stack" << r2::linefeed2;

				EXPECT_FALSE( lua_isnil( lua_state_obj, 1 ) );

				std::cout << r2::linefeed2;

				EXPECT_TRUE( lua_isnumber( lua_state_obj, 1 ) );

				std::cout << r2::linefeed2;

				EXPECT_TRUE( lua_isstring( lua_state_obj, 1 ) );

				std::cout << r2::linefeed2;

				EXPECT_FALSE( lua_isfunction( lua_state_obj, 1 ) );

				std::cout << r2::linefeed2;

				EXPECT_TRUE( lua_isinteger( lua_state_obj, 1 ) );

				std::cout << r2::linefeed2;

				EXPECT_FALSE( lua_isuserdata( lua_state_obj, 1 ) );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
