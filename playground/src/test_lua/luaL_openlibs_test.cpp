#include "pch.h"
#include "luaL_openlibs_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"


//
// http://lua-users.org/wiki/MathLibraryTutorial
//


namespace luaL_openlibs_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_openlibs";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();

			std::cout << r2::split;

			std::cout << "Note : luaL_openlibs - 함수들을 사용하려면 로드하자." << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( const char* command = "a = math.sin( math.pi * 0.5 )" );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Test 1 : Library 로드 전" << r2::linefeed2;

				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Test 2 : Library 로드" << r2::linefeed2;

				PROCESS_MAIN( luaL_openlibs( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Test 3 : Library 로드 후" << r2::linefeed2;

				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, -1 ) );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) );
				std::cout << "a : " << a << r2::linefeed;
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
