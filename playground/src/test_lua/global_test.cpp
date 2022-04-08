#include "pch.h"
#include "global_test.h"

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

			std::cout << "Note : lua_getglobal is Find And Push 2 Stack" << r2::linefeed;
			std::cout << "Note : lua_gettop returns the Stack Size" << r2::linefeed;
			std::cout << "Note : -1 is Top of Stack" << r2::linefeed;

			std::cout << r2::split;

			{
				EXPECT_EQ( 0, lua_gettop( lua_state_obj ) );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "a" ) );
				EXPECT_EQ( LUA_TNIL, type );

				std::cout << r2::linefeed;

				EXPECT_EQ( 1, lua_gettop( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, "b = 7" ) );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "b" ) );
				EXPECT_EQ( LUA_TNUMBER, type );

				std::cout << r2::linefeed;

				EXPECT_EQ( 2, lua_gettop( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const auto stack_size = lua_gettop( lua_state_obj ) );

				std::cout << r2::linefeed;

				std::cout << "+ Show Stack" << r2::linefeed;
				for( int i = 1; stack_size >= i; ++i )
				{
					std::cout << "[" << i << "]" << luaL_typename( lua_state_obj, i ) << "   ";

					switch( lua_type( lua_state_obj, i ) )
					{
					case LUA_TNUMBER:
						std::cout << lua_tonumber( lua_state_obj, i ) << r2::linefeed;
						break;
					case LUA_TNIL:
						std::cout << "nil" << r2::linefeed;
						break;
					default:
						std::cout << "( '_')y-~" << r2::linefeed;
						break;
					}
				}
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


			return r2cm::eTestEndAction::Pause;
		};
	}
}