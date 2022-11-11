#include "pch.h"
#include "luaL_openlibs_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"


//
// http://lua-users.org/wiki/MathLibraryTutorial
//


namespace luaL_openlibs_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_openlibs";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			std::cout << r2cm::split;

			std::cout << "Note : luaL_openlibs - 함수들을 사용하려면 로드하자." << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const char* command = "a = math.sin( math.pi * 0.5 )" );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Test 1 : Library 로드 전" << r2cm::linefeed2;

				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Test 2 : Library 로드" << r2cm::linefeed2;

				PROCESS_MAIN( luaL_openlibs( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Test 3 : Library 로드 후" << r2cm::linefeed2;

				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, -1 ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( const auto a = lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "a : " << a << r2cm::linefeed;
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
