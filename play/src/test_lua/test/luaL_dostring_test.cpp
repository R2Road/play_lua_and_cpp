#include "luaL_dostring_test.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

namespace luaL_dostring_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_dostring";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECL_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2tm::split;

			{
				DECL_MAIN( const char* command = "a = 7 + 11" );

				std::cout << r2tm::linefeed2;

				DECL_MAIN( const int lua_result = luaL_dostring( lua_state_obj, command ) );
				EXPECT_TRUE( LUA_OK == lua_result );
			}

			std::cout << r2tm::split;

			{
				DECL_MAIN( const char* command = "a = 7 + " );

				std::cout << r2tm::linefeed2;

				DECL_MAIN( const int lua_result = luaL_dostring( lua_state_obj, command ) );
				EXPECT_FALSE( LUA_OK == lua_result );

				std::cout << r2tm::linefeed2;

				DECL_MAIN( const auto error_message = lua_tostring( lua_state_obj, -1 ) );
				std::cout << r2tm::tab << "error message : " << error_message << r2tm::linefeed;
			}

			std::cout << r2tm::split;

			PROC_SUB( lua_close( lua_state_obj ) );

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}