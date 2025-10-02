#include "luaL_openlibs_test.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"


//
// http://lua-users.org/wiki/MathLibraryTutorial
//


namespace luaL_openlibs_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_openlibs";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			std::cout << "Note : luaL_openlibs - 함수들을 사용하려면 로드하자." << r2tm::linefeed;

			LS();

			DECL_MAIN( const char* command = "a = math.sin( math.pi * 0.5 )" );

			LS();

			{
				std::cout << r2tm::tab << "+ Test 1 : Library 로드 전" << r2tm::linefeed2;

				PROC_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Test 2 : Library 로드" << r2tm::linefeed2;

				PROC_MAIN( luaL_openlibs( lua_state_obj ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Test 3 : Library 로드 후" << r2tm::linefeed2;

				PROC_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );

				LF();

				PROC_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, -1 ) );

				LF();

				DECL_MAIN( const auto a = lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "a : " << a << r2tm::linefeed;
			}

			LS();


			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}
}
