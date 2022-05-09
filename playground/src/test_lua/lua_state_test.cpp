#include "pch.h"
#include "lua_state_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_constant.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace lua_state_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "luaL_newstate, lua_close";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			std::cout << "Note : luaL_newstate - lua_State 생성." << r2cm::linefeed;
			std::cout << "Note : lua_close - lua_State 제거." << r2cm::linefeed;

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
