#include "pch.h"
#include "lua_dostring_test.h"

#include <string>

#include "base/r2_eTestResult.h"

namespace lua_dostring_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "DoString";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;


			lua_State* lua_state_obj = luaL_newstate();

			std::string command;
			std::cout << r2::tab << "+ Variable" << r2::linefeed2;
			std::cout << r2::tab2 << "std::string command;" << r2::linefeed;


			std::cout << r2::split;

			{
				command = "a = 7 + 11";
				std::cout << r2::tab << "+ Command String" << r2::linefeed2;
				std::cout << r2::tab2 << "command = \"a = 7 + 11\";" << r2::linefeed;
			}

			std::cout << r2::linefeed2;

			{
				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "luaL_dostring( lua_state_obj, command.c_str() )" << r2::linefeed;

				const int result = luaL_dostring( lua_state_obj, command.c_str() );
				if( result != LUA_OK )
				{
					const auto error_message = lua_tostring( lua_state_obj, -1 );

					std::cout << r2::tab3 << "Command Failed " << r2::linefeed;
					std::cout << r2::tab3 << error_message << r2::linefeed;
				}
				else
				{
					std::cout << r2::tab3 << "Command Success" << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				command = "a = 7 + ";
				std::cout << r2::tab << "+ Command String" << r2::linefeed2;
				std::cout << r2::tab2 << "command = \"a = 7 + \";" << r2::linefeed;
			}

			std::cout << r2::linefeed2;

			{
				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "luaL_dostring( lua_state_obj, command.c_str() )" << r2::linefeed;

				const int result = luaL_dostring( lua_state_obj, command.c_str() );
				if( result != LUA_OK )
				{
					const auto error_message = lua_tostring( lua_state_obj, -1 );

					std::cout << r2::tab3 << "Command Failed " << r2::linefeed;
					std::cout << r2::tab3 << error_message << r2::linefeed;
				}
				else
				{
					std::cout << r2::tab3 << "Command Success" << r2::linefeed;
				}
			}

			std::cout << r2::split;

			lua_close( lua_state_obj );

			return r2::eTestResult::RunTest;
		};
	}
}

namespace step
{
	void DoString()
	{
		
	}
}
