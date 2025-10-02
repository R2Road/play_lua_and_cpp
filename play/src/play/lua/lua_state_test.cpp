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
			LS();

			DECL_MAIN( lua_State* lua_state_obj = nullptr );

			LS();

			//
			// Make Lua State
			//
			{
				OUT_NOTE( "luaL_newstate - lua_State 생성." );

				LF();

				PROC_MAIN( lua_state_obj = luaL_newstate() );
			}

			LS();

			//
			// Close Lua State
			//
			{
				OUT_NOTE( "lua_close - lua_State 제거." );

				LF();

				PROC_MAIN( lua_close( lua_state_obj ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}
