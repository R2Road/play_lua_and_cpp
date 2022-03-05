#include "pch.h"
#include "lua_type_check_test.h"

#include "base/r2cm_eTestEndAction.h"

namespace lua_type_check_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Check";
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
				step_helper::LuaDoString_Silent( lua_state_obj, "a = 7 + 11", 3u );

				std::cout << r2::tab << "+ Do String" << r2::linefeed2;
				std::cout << r2::tab2 << "luaL_dostring( lua_state_obj, \"a = 7 + 11\" )" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				const int type = lua_getglobal( lua_state_obj, "a" );

				std::cout << r2::tab << "+ Type Check And Push 2 Stack" << r2::linefeed2;
				std::cout << r2::tab2 << "const int type = lua_getglobal( lua_state_obj, \"a\" );" << r2::linefeed;
				std::cout << r2::tab3 << "Result : ";
				step_helper::PrintType( "a", type );
			}

			std::cout << r2::split;

			{
				const int type = lua_type( lua_state_obj, 1 );

				std::cout << r2::tab << "+ Type Check In Stack 1" << r2::linefeed2;
				std::cout << r2::tab2 << "const int type = lua_type( lua_state_obj, 1 );" << r2::linefeed;
				std::cout << r2::tab3 << "Result : ";
				step_helper::PrintType( "1", type );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Type Check In Stack 2" << r2::linefeed2;

				{
					const int boolean = lua_isnil( lua_state_obj, 1 );
					std::cout << r2::tab2 << "const int boolean = lua_isnil( lua_state_obj, 1 );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << ( boolean ? "true" : "false" );
				}

				std::cout << r2::linefeed2;

				{
					const int boolean = lua_isnumber( lua_state_obj, 1 );
					std::cout << r2::tab2 << "const int boolean = lua_isnumber( lua_state_obj, 1 );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << ( boolean ? "true" : "false" );
				}

				std::cout << r2::linefeed2;

				{
					const int boolean = lua_isstring( lua_state_obj, 1 );
					std::cout << r2::tab2 << "const int boolean = lua_isstring( lua_state_obj, 1 );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << ( boolean ? "true" : "false" );
				}

				std::cout << r2::linefeed2;

				{
					const int boolean = lua_iscfunction( lua_state_obj, 1 );
					std::cout << r2::tab2 << "const int boolean = lua_iscfunction( lua_state_obj, 1 );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << ( boolean ? "true" : "false" );
				}

				std::cout << r2::linefeed2;

				{
					const int boolean = lua_isinteger( lua_state_obj, 1 );
					std::cout << r2::tab2 << "const int boolean = lua_isinteger( lua_state_obj, 1 );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << ( boolean ? "true" : "false" );
				}

				std::cout << r2::linefeed2;

				{
					const int boolean = lua_isuserdata( lua_state_obj, 1 );
					std::cout << r2::tab2 << "const int boolean = lua_isuserdata( lua_state_obj, 1 );" << r2::linefeed;
					std::cout << r2::tab3 << "Result : " << ( boolean ? "true" : "false" );
				}

				std::cout << r2::linefeed2;
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::None;
		};
	}
}
