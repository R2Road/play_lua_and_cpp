#include "play_sol2.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

#include "lua_header_package.h"

namespace play_sol2
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUT_SOURCE_READY_N_BEGIN;
				struct vars {
					int boop = 0;
				};

				sol::state lua;
				lua.new_usertype<vars>( "vars", "boop", &vars::boop );
				lua.script(
					"beep = vars.new()"
					"\n"  "beep.boop = 1"
				);
				OUT_SOURCE_END;

				LF();

				EXPECT_EQ( 1, lua.get<vars>( "beep" ).boop );

				LF();

				OUT_VALUE( lua.get<vars>( "beep" ).boop );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}