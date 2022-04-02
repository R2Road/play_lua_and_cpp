#include "pch.h"
#include "luaL_dofile_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace luaL_dofile_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_dofile";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();

			std::cout << r2::split;

			PROCESS_MAIN( luaL_openlibs( lua_state_obj ) );

			std::cout << r2::split;

			//
			// Test x 0
			//
			{
				std::cout << r2::tab << "+ Test 0" << r2::linefeed2;

				EXPECT_NE( LUA_OK, luaL_dofile( lua_state_obj, "resources/step_DoFile_00.lua" ) );

				const auto error_message = lua_tostring( lua_state_obj, -1 );
				std::cout << "error_message : " << error_message << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Test x 1
			//
			{
				std::cout << r2::tab << "+ Test 1" << r2::linefeed2;

				EXPECT_NE( LUA_OK, luaL_dofile( lua_state_obj, "resources/step_DoFile_01.lua" ) );
				
				const auto error_message = lua_tostring( lua_state_obj, -1 );
				std::cout << "error_message : " << error_message << r2::linefeed;
			}

			std::cout << r2::split;

			//
			// Test x 2
			//
			{
				std::cout << r2::tab << "+ Test 2" << r2::linefeed2;

				EXPECT_EQ( LUA_OK, luaL_dofile( lua_state_obj, "resources/step_DoFile_02.lua" ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, -1 ) );

				DECLARATION_MAIN( const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) );
				std::cout << "a : " << a << r2::linefeed;
			}

			std::cout << r2::split;

			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}
}
