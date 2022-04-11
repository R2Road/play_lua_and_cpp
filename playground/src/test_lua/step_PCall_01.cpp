#include "pch.h"
#include "step_PCall_01.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace function_cpp2lua_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function cpp2lua";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			


			std::cout << "Call : luaL_openlibs" << r2::linefeed;
			luaL_openlibs( lua_state_obj );

			std::cout << r2::linefeed;

			if( !test_lua_helper::LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, "resources/step_PCall_01.lua" ) ) )
			{
				//return;
			}

			std::cout << r2::linefeed;

			//
			// Test x 0
			//
			{
				std::cout << "# Test 0 : Call With Arg x 1" << r2::linefeed;

				lua_getglobal( lua_state_obj, "TestFunction" );
				if( lua_isfunction( lua_state_obj, -1 ) )
				{
					std::cout << "TestFunction is Function" << r2::linefeed;

					lua_pushnumber( lua_state_obj, 123 );

					if( test_lua_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ) ) )
					{
						std::cout << "Result : TestFunction : " << static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) << r2::linefeed;
					}
				}
				else
				{
					std::cout << "Is Not Function" << r2::linefeed;
				}
			}

			std::cout << r2::linefeed;

			//
			// Test x 1
			//
			{
				std::cout << "# Test 1 : Call With Arg x 2" << r2::linefeed;

				lua_getglobal( lua_state_obj, "TestFunction" );
				if( lua_isfunction( lua_state_obj, -1 ) )
				{
					std::cout << "TestFunction is Function" << r2::linefeed;

					lua_pushnumber( lua_state_obj, 123 );
					lua_pushnumber( lua_state_obj, 456 );

					if( test_lua_helper::LuaErrorCheck( lua_state_obj, lua_pcall( lua_state_obj, 2, 1, 0 ) ) )
					{
						std::cout << "Result : TestFunction : " << static_cast<float>( lua_tonumber( lua_state_obj, -1 ) ) << r2::linefeed;
					}
				}
				else
				{
					std::cout << "Is Not Function" << r2::linefeed;
				}
			}




			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
