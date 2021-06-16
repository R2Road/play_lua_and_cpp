#include "pch.h"
#include "lua_getglobal_test.h"

#include "base/r2_eTestResult.h"

namespace lua_getglobal_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetGlobal";
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
				//
				// Push Variable "a"
				//
				const int type = lua_getglobal( lua_state_obj, "a" );

				std::cout << r2::tab << "lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed;
				std::cout << r2::tab2 << "Result : ";
				step_helper::PrintType( "a", type );
			}

			std::cout << r2::split;

			{
				const std::string command = "a = 7";
				std::cout << r2::tab << "+ Command String" << r2::linefeed2;
				std::cout << r2::tab2 << "const std::string command = \"a = 7\";" << r2::linefeed2;


				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "luaL_dostring( lua_state_obj, command.c_str() )" << r2::linefeed;

				step_helper::DoString( lua_state_obj, command.c_str(), 3u );
			}

			std::cout << r2::split;
				
			{
				const int type = lua_getglobal( lua_state_obj, "a" );

				std::cout << r2::tab << "lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed;
				std::cout << r2::tab2 << "Result : ";
				step_helper::PrintType( "a", type );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2::eTestResult::RunTest;
		};
	}
}