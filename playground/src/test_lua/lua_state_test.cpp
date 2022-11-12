#include "lua_state_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace lua_state_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_newstate, lua_close";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_NOTE( "luaL_newstate - lua_State 생성." );
			OUTPUT_NOTE( "lua_close - lua_State 제거." );

			std::cout << r2cm::split;

			DECLARATION_MAIN( lua_State* lua_state_obj = nullptr );

			std::cout << r2cm::split;

			//
			// Make Lua State
			//
			{
				std::cout << r2cm::tab << "+ Create" << r2cm::linefeed2;

				PROCESS_MAIN( lua_state_obj = luaL_newstate() );
			}

			std::cout << r2cm::split;

			//
			// Close Lua State
			//
			{
				std::cout << r2cm::tab << "+ Close" << r2cm::linefeed2;

				PROCESS_MAIN( lua_close( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
