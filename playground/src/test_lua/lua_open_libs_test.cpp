#include "pch.h"
#include "lua_open_libs_test.h"

#include "base/r2_eTestResult.h"


//
// http://lua-users.org/wiki/MathLibraryTutorial
//


namespace lua_open_libs_test
{
	r2cm::iItem::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Open Libs";
		};
	}
	r2cm::iItem::DoFunc Basic::GetDoFunction()
	{
		return []()->r2cm::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;


			const char* command = "a = math.sin( math.pi * 0.5 )";
			std::cout << r2::tab << "+ Command String" << r2::linefeed2;
			std::cout << r2::tab2 << "Command : " << command << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "step_helper::LuaDoString( lua_state_obj, command )" << r2::linefeed2;

				step_helper::LuaDoString( lua_state_obj, command );
			}

			std::cout << r2::split;

			{
				luaL_openlibs( lua_state_obj );

				std::cout << r2::tab << "+ Call" << r2::linefeed2;
				std::cout << r2::tab2 << "luaL_openlibs( lua_state_obj )" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "step_helper::LuaDoString( lua_state_obj, command )" << r2::linefeed2;

				step_helper::LuaDoString( lua_state_obj, command );
				lua_getglobal( lua_state_obj, "a" );
				if( lua_isnumber( lua_state_obj, -1 ) )
				{
					const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
					std::cout << "result : " << "a : " << a << r2::linefeed;
				}
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestResult::RunTest;
		};
	}
}
