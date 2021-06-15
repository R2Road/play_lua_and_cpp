#include "pch.h"
#include "step_IsNumber.h"

#include "base/r2_eTestResult.h"

namespace lua_isnumber_test
{
	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "IsNumber";
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
				//
				// Push to Stack "a"
				//
				lua_getglobal( lua_state_obj, "a" );

				//
				// Test 1
				//
				{
					std::cout << "lua_tonumber : -1 " << r2::linefeed;

					//
					// -1 : is Last Value Index
					//
					if( lua_isnumber( lua_state_obj, -1 ) )
					{
						const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
						std::cout << "result : " << "a : " << a << r2::linefeed;
					}
				}

				std::cout << r2::linefeed;

				//
				// Test 2
				//
				{
					std::cout << "lua_tonumber : 1 " << r2::linefeed;

					//
					// 1 : is First Stack Index
					//
					if( lua_isnumber( lua_state_obj, 1 ) )
					{
						const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) );
						std::cout << "result : " << "a : " << a << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			lua_close( lua_state_obj );

			return r2::eTestResult::RunTest;
		};
	}
}
