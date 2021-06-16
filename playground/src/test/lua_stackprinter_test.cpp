#include "pch.h"
#include "lua_stackprinter_test.h"

#include "base/r2_eTestResult.h"

namespace lua_stackprinter_test
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
				const int stack_size = lua_gettop( lua_state_obj );

				std::cout << r2::tab << "+ Print Stack" << r2::linefeed2;
				std::cout << r2::tab2 << "const int stack_size = lua_gettop( lua_state_obj );" << r2::linefeed;
				std::cout << r2::tab3 << "Stack Count : " << stack_size << r2::linefeed2;

				for( int i = 1; stack_size >= i; ++i )
				{
					std::cout << r2::tab << i << r2::tab << luaL_typename( lua_state_obj, i ) << r2::tab;

					switch( lua_type( lua_state_obj, i ) )
					{
					case LUA_TNUMBER:
						std::cout << lua_tonumber( lua_state_obj, i ) << r2::linefeed;
						break;
					case LUA_TSTRING:
						std::cout << lua_tostring( lua_state_obj, i ) << r2::linefeed;
						break;
					case LUA_TBOOLEAN:
						std::cout << ( lua_toboolean( lua_state_obj, i ) ? "true" : "false" ) << r2::linefeed;
						break;
					case LUA_TNIL:
						std::cout << "nil" << r2::linefeed;
						break;
					default:
						std::cout << lua_topointer( lua_state_obj, i ) << r2::linefeed;
						break;
					}
				}
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