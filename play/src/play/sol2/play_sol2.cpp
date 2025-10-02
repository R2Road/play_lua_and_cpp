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



	std::string bind_function( int D_count, std::string original )
	{
		// Create a string with the letter 'D' "D_count" times,
		// append it to 'original'
		return original + std::string( D_count, 'D' );
	}
	r2tm::TitleFunctionT Bind_Function::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Bind Function";
		};
	}
	r2tm::DoFunctionT Bind_Function::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUT_SOURCE_READY_N_BEGIN;
				sol::state lua;

				lua["my_func"] = bind_function;					// way 1
				lua.set( "my_func", bind_function );			// way 2
				lua.set_function( "my_func", bind_function );	// way 3

				// This function is now accessible as 'my_func' in
				// lua scripts / code run on this state:
				lua.script( "some_str = my_func( 2, 'Da' )" );
				OUT_SOURCE_END;

				LF();

				// Read out the global variable we stored in 'some_str' in
				// the quick lua code we just executed
				DECL_MAIN( std::string some_str = lua["some_str"] );
				EXPECT_EQ( some_str, "DaDD" );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}