#include "pch.h"
#include "lua_table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace lua_table_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Table : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );
			DECLARATION_SUB( luaL_openlibs( lua_state_obj ) );

			std::cout << r2::split;

			{
				//
				// Test x 1
				//
				{
					std::cout << "# Test 1" << r2::linefeed;

					if( step_helper_deprecated::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "resources/step_GetTable_01.lua" ), "luaL_dofile" ) )
					{
						lua_getglobal( lua_state_obj, "data" );
						if( lua_istable( lua_state_obj, -1 ) )
						{
							std::cout << "data is Table" << r2::linefeed;
							std::cout << r2::linefeed;


							lua_pushstring( lua_state_obj, "name" );
							lua_gettable( lua_state_obj, -2 );
							const std::string name = lua_tostring( lua_state_obj, -1 );
							std::cout << "name : " << name.c_str() << r2::linefeed;
							lua_pop( lua_state_obj, 1 );


							lua_pushstring( lua_state_obj, "age" );
							lua_gettable( lua_state_obj, -2 );
							const int age = (int)lua_tointeger( lua_state_obj, -1 );
							std::cout << "age : " << age << r2::linefeed;
							lua_pop( lua_state_obj, 1 );
						}
						else
						{
							std::cout << "Is Not Table" << r2::linefeed;
						}
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


namespace step
{
	void GetTable()
	{
		
	}
}
