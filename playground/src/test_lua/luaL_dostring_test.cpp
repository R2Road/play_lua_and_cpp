#include "pch.h"
#include "luaL_dostring_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

namespace luaL_dostring_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_dostring";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* command = "a = 7 + 11" );

				std::cout << r2cm::linefeed2;

				DECLARATION_MAIN( const int lua_result = luaL_dostring( lua_state_obj, command ) );
				EXPECT_TRUE( LUA_OK == lua_result );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* command = "a = 7 + " );

				std::cout << r2cm::linefeed2;

				DECLARATION_MAIN( const int lua_result = luaL_dostring( lua_state_obj, command ) );
				EXPECT_FALSE( LUA_OK == lua_result );

				std::cout << r2cm::linefeed2;

				DECLARATION_MAIN( const auto error_message = lua_tostring( lua_state_obj, -1 ) );
				std::cout << r2cm::tab << "error message : " << error_message << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}