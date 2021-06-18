#include "pch.h"
#include "lua_type_check_test.h"

#include "base/r2_eTestResult.h"

namespace lua_type_check_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Check";
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
				const std::string command = "a = 7 + 11";
				std::cout << r2::tab << "+ Command String" << r2::linefeed2;
				std::cout << r2::tab2 << "const std::string command = \"a = 7 + 11\";" << r2::linefeed2;


				std::cout << r2::tab << "+ Process" << r2::linefeed2;
				std::cout << r2::tab2 << "luaL_dostring( lua_state_obj, command.c_str() )" << r2::linefeed;

				step_helper::DoString( lua_state_obj, command.c_str(), 3u );
			}

			std::cout << r2::split;

			{
				lua_getglobal( lua_state_obj, "a" );

				std::cout << r2::tab << "+ Push to Stack \"a\"" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Process" << r2::linefeed2;

				std::cout << r2::tab2 << "lua_isnumber( lua_state_obj, -1 )" << r2::linefeed;
				std::cout << r2::tab3 << "Result : " << ( lua_isnumber( lua_state_obj, -1 ) ? "O" : "X" ) << r2::linefeed2;

				std::cout << r2::tab << "Note : -1 is Top of Stack" << r2::linefeed2;


				std::cout << r2::tab2 << "lua_tonumber( lua_state_obj, -1 )" << r2::linefeed;
				if( lua_isnumber( lua_state_obj, -1 ) )
				{
					const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
					std::cout << r2::tab3 << "Result : " << "a = " << a << r2::linefeed;
				}
				else
				{
					std::cout << r2::tab3 << "- Failed" << r2::linefeed;
				}
				std::cout << r2::linefeed;


				std::cout << r2::tab2 << "lua_tonumber( lua_state_obj, 1 )" << r2::linefeed;
				if( lua_isnumber( lua_state_obj, 1 ) )
				{
					const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
					std::cout << r2::tab3 << "Result : " << "a = " << a << r2::linefeed;
				}
				else
				{
					std::cout << r2::tab3 << "- Failed" << r2::linefeed;
				}
				std::cout << r2::linefeed;

				std::cout << r2::tab << "Note : 1 is Bottom of Stack" << r2::linefeed2;
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2::eTestResult::RunTest;
		};
	}
}
