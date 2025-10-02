#include "luaL_dofile_test.h"

#include <filesystem>

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

namespace luaL_dofile_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_dofile";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			PROC_MAIN( luaL_openlibs( lua_state_obj ) );

			LS();

			//
			// Test x 0
			//
			{
				std::cout << r2tm::tab << "+ Test 0 : 파일 없음" << r2tm::linefeed2;

				EXPECT_NE( LUA_OK, luaL_dofile( lua_state_obj, "resources/luaL_dofile_test_00.lua" ) );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_tostring( lua_state_obj, -1 ) );
			}

			LS();

			//
			// Test x 1
			//
			{
				std::cout << r2tm::tab << "+ Test 1 : Script 에러" << r2tm::linefeed2;

				const std::filesystem::path p( "resources/luaL_dofile_test_01.lua");
				OUT_FILE( p.string().c_str() );

				std::cout << r2tm::linefeed;

				EXPECT_NE( LUA_OK, luaL_dofile( lua_state_obj, p.string().c_str() ) );
				
				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_tostring( lua_state_obj, -1 ) );
			}

			LS();

			//
			// Test x 2
			//
			{
				std::cout << r2tm::tab << "+ Test 2" << r2tm::linefeed2;

				const std::filesystem::path p( "resources/luaL_dofile_test_02.lua" );
				OUT_FILE( p.string().c_str() );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( LUA_OK, luaL_dofile( lua_state_obj, p.string().c_str() ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, -1 ) );

				DECL_MAIN( const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) );
				std::cout << "a : " << a << r2tm::linefeed;
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}
