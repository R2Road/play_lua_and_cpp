#include "pch.h"
#include "lua_getglobal_test.h"

#include "base/r2_eTestResult.h"

namespace lua_getglobal_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetGlobal";
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
				const int type = lua_getglobal( lua_state_obj, "a" );

				std::cout << r2::tab << "+ Find And Push 2 Stack" << r2::linefeed2;
				std::cout << r2::tab2 << "const int type = lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed;
				std::cout << r2::tab3 << "Result : ";
				step_helper::PrintType( "a", type );
			}

			std::cout << r2::split;

			{
				{
					const char* command = "a = 7";
					std::cout << r2::tab << "+ Command String" << r2::linefeed2;
					std::cout << r2::tab2 << "const char* command = \"a = 7\";" << r2::linefeed3;


					std::cout << r2::tab << "+ Process" << r2::linefeed2;
					std::cout << r2::tab2 << "luaL_dostring( lua_state_obj, command )" << r2::linefeed;

					step_helper::LuaDoString( lua_state_obj, command, 3u );
				}

				std::cout << r2::linefeed2;

				{
					const int type = lua_getglobal( lua_state_obj, "a" );

					std::cout << r2::tab << "+ Find And Push 2 Stack" << r2::linefeed2;
					std::cout << r2::tab2 << "const int type = lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : ";
					step_helper::PrintType( "a", type );
				}

				std::cout << r2::linefeed2;

				{
					const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );

					std::cout << r2::tab << "+ Get Value" << r2::linefeed2;
					std::cout << r2::tab2 << "const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << "a = " << a << r2::linefeed2;

					std::cout << r2::tab << "Note : -1 is Top of Stack" << r2::linefeed;
				}
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::None;
		};
	}
}