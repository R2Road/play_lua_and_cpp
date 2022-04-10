#include "pch.h"
#include "lua_state_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

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
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			std::cout << "Note : luaL_newstate - lua_State 생성." << r2::linefeed;
			std::cout << "Note : lua_close - lua_State 제거." << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( lua_State* lua_state_obj = nullptr );

			std::cout << r2::split;

			//
			// Make Lua State
			//
			{
				std::cout << r2::tab << "+ Create" << r2::linefeed2;

				PROCESS_MAIN( lua_state_obj = luaL_newstate() );
			}

			std::cout << r2::split;

			//
			// Close Lua State
			//
			{
				std::cout << r2::tab << "+ Close" << r2::linefeed2;

				PROCESS_MAIN( lua_close( lua_state_obj ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}
