#include "lua_state_test.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace lua_state_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_newstate, lua_close";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECL_MAIN( lua_State* lua_state_obj = nullptr );

			std::cout << r2tm::split;

			//
			// Make Lua State
			//
			{
				OUT_NOTE( "luaL_newstate - lua_State 생성." );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_state_obj = luaL_newstate() );
			}

			std::cout << r2tm::split;

			//
			// Close Lua State
			//
			{
				OUT_NOTE( "lua_close - lua_State 제거." );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_close( lua_state_obj ) );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}
