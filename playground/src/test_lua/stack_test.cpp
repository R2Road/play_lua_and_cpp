#include "pch.h"
#include "stack_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

//
// lua_CFunction : typedef int (*lua_CFunction) (lua_State *L);
//
int cclosure_test_function( lua_State* )
{
	return 0;
}

namespace stack_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = nullptr );
			PROCESS_SUB( lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push( info : lua.h 233 line )" << r2::linefeed2;

				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );

				std::cout << r2::linefeed;

				std::cout << r2::tab << "Stack Count : " << stack_count << r2::linefeed;
				for( int i = 1, ri = -stack_count; stack_count >= i; ++i, ++ri )
				{
					std::cout << r2::tab << "[" << i << "]" << r2::tab << "[" << ri << "]" << r2::tab << luaL_typename( lua_state_obj, i ) << r2::tab;

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

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT StackPrinterTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Printer";
		};
	}
	r2cm::iItem::DoFuncT StackPrinterTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				PROCESS_SUB( lua_pushnil( lua_state_obj ) );
				PROCESS_SUB( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_SUB( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_SUB( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_SUB( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_SUB( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_SUB( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
