#include "pch.h"
#include "step_GetGlobal.h"

#include "base/r2_eTestResult.h"
#include "step_helper.h"

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

			std::cout << r2::split;

			lua_State* lua_state_obj = luaL_newstate();

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