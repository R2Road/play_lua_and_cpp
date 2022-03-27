#include "pch.h"
#include "lua_stack_printer_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace lua_stack_printer_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Printer";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				DECLARATION_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, "a = 15" ) );
				DECLARATION_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, "c = 7" ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "b" ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "c" ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "d" ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( step_helper_deprecated::LuaViewAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}