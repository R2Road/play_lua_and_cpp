#include "pch.h"
#include "lua_stack_printer_test.h"

#include "base/r2_eTestResult.h"

namespace lua_stack_printer_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Printer";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Command String" << r2::linefeed2;
				std::cout << r2::tab2 << "const char* command = \"a = 15\";" << r2::linefeed;

				const char* command = "a = 15";
				step_helper::DoString( lua_state_obj, command, 3u );
			}

			std::cout << r2::linefeed2;

			{
				std::cout << r2::tab << "+ Command String" << r2::linefeed2;
				std::cout << r2::tab2 << "const char* command = \"c = 7\";" << r2::linefeed;

				const char* command = "c = 7";
				step_helper::DoString( lua_state_obj, command, 3u );
			}

			std::cout << r2::linefeed2;

			{
				lua_getglobal( lua_state_obj, "a" );
				lua_getglobal( lua_state_obj, "b" );
				lua_getglobal( lua_state_obj, "c" );
				lua_getglobal( lua_state_obj, "d" );

				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_getglobal( lua_state_obj, \"b\" );" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_getglobal( lua_state_obj, \"c\" );" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_getglobal( lua_state_obj, \"d\" );" << r2::linefeed2;
			}

			std::cout << r2::split;

			{
				step_helper::LuaViewAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				lua_settop( lua_state_obj, 0 );

				int stack_size = lua_gettop( lua_state_obj );
				lua_pop( lua_state_obj, stack_size );

				std::cout << r2::tab << "+ Clear Stack" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_settop( lua_state_obj, 0 );" << r2::linefeed;
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2::eTestResult::RunTest;
		};
	}
}