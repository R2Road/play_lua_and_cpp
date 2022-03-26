#include "pch.h"
#include "lua_getglobal_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace lua_getglobal_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_getglobal";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << "+ Find And Push 2 Stack" << r2::linefeed2;
				DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "a" ) );
				PROCESS_MAIN( step_helper::PrintType( "a", type ) );
			}

			std::cout << r2::split;

			{
				{
					DECLARATION_MAIN( const char* command = "a = 7" );
					PROCESS_MAIN( step_helper::LuaDoString( lua_state_obj, command, 1u ) );
				}

				std::cout << r2::linefeed3;

				{
					std::cout << "+ Find And Push 2 Stack" << r2::linefeed2;
					DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "a" ) );
					PROCESS_MAIN( step_helper::PrintType( "a", type ) );
				}

				std::cout << r2::linefeed3;

				{
					std::cout << "+ Get Value" << r2::linefeed2;
					DECLARATION_MAIN( const auto a = static_cast<int>( lua_tonumber( lua_state_obj, -1 ) ) );
					std::cout << r2::tab << "Result : " << "a = " << a << r2::linefeed2;

					std::cout << "Note : -1 is Top of Stack" << r2::linefeed;
				}
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}
}