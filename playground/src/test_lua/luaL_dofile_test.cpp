#include "pch.h"
#include "luaL_dofile_test.h"

#include <filesystem>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

namespace luaL_dofile_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_dofile";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			lua_State* lua_state_obj = luaL_newstate();

			std::cout << r2cm::split;

			PROCESS_MAIN( luaL_openlibs( lua_state_obj ) );

			std::cout << r2cm::split;

			//
			// Test x 0
			//
			{
				std::cout << r2cm::tab << "+ Test 0 : 파일 없음" << r2cm::linefeed2;

				EXPECT_NE( LUA_OK, luaL_dofile( lua_state_obj, "resources/luaL_dofile_test_00.lua" ) );

				const auto error_message = lua_tostring( lua_state_obj, -1 );
				std::cout << "error_message : " << error_message << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			//
			// Test x 1
			//
			{
				std::cout << r2cm::tab << "+ Test 1 : Script 에러" << r2cm::linefeed2;

				const std::filesystem::path p( "resources/luaL_dofile_test_01.lua");
				SHOW_FILE( p.string().c_str() );

				std::cout << r2cm::linefeed;

				EXPECT_NE( LUA_OK, luaL_dofile( lua_state_obj, p.string().c_str() ) );
				
				const auto error_message = lua_tostring( lua_state_obj, -1 );
				std::cout << "error_message : " << error_message << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			//
			// Test x 2
			//
			{
				std::cout << r2cm::tab << "+ Test 2" << r2cm::linefeed2;

				const std::filesystem::path p( "resources/luaL_dofile_test_02.lua" );
				SHOW_FILE( p.string().c_str() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( LUA_OK, luaL_dofile( lua_state_obj, p.string().c_str() ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, -1 ) );

				DECLARATION_MAIN( const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) );
				std::cout << "a : " << a << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
