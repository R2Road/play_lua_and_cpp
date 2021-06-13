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
				std::cout << "lua_getglobal a" << r2::linefeed;

				//
				// Push Variable "a"
				//
				const int type = lua_getglobal( lua_state_obj, "a" );
				step_helper::PrintType( "a", type );
			}

			std::cout << r2::linefeed;

			{
				const std::string command = "b = 7";
				std::cout << "Command : " << command.c_str() << r2::linefeed;

				//
				// Do String
				//
				const int result = luaL_dostring( lua_state_obj, command.c_str() );
				if( result != LUA_OK )
				{
					const auto error_message = lua_tostring( lua_state_obj, -1 );

					std::cout << "Command Failed " << r2::linefeed;
					std::cout << error_message << r2::linefeed;
				}
				else
				{
					std::cout << "Command Success" << r2::linefeed;
				}

				std::cout << "lua_getglobal b" << r2::linefeed;

				//
				// Push Variable "a"
				//
				const int type = lua_getglobal( lua_state_obj, "b" );
				step_helper::PrintType( "b", type );
			}

			lua_close( lua_state_obj );

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}