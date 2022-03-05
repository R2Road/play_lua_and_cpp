#include "pch.h"
#include "lua_stack_clear_test.h"

#include "base/r2_eTestResult.h"

namespace lua_stack_clear_test
{
	r2::iItem::TitleFunc SetTop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : Set Top";
		};
	}
	r2::iItem::DoFunc SetTop::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				step_helper::LuaInsertDummyValueInStack( lua_state_obj );

				std::cout << r2::tab << "+ Fill Stack" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				step_helper::LuaViewAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				lua_settop( lua_state_obj, 0 );

				std::cout << r2::tab << "+ Clear Stack" << r2::linefeed2;
				std::cout << r2::tab2 << "lua_settop( lua_state_obj, 0 );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				step_helper::LuaViewAllStack( lua_state_obj );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2::eTestResult::RunTest;
		};
	}



	r2::iItem::TitleFunc Pop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : Pop";
		};
	}
	r2::iItem::DoFunc Pop::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				step_helper::LuaInsertDummyValueInStack( lua_state_obj );

				std::cout << r2::tab << "+ Fill Stack" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				step_helper::LuaViewAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				int stack_size = lua_gettop( lua_state_obj );
				lua_pop( lua_state_obj, stack_size );

				std::cout << r2::tab << "+ Clear Stack" << r2::linefeed2;
				std::cout << r2::tab2 << "int stack_size = lua_gettop( lua_state_obj );" << r2::linefeed;
				std::cout << r2::tab2 << "lua_pop( lua_state_obj, stack_size );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				step_helper::LuaViewAllStack( lua_state_obj );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2::eTestResult::RunTest;
		};
	}
}