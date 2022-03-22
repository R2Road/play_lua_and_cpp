#include "pch.h"
#include "r2lua_push_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "r2lua/r2lua_Value.h"
#include "step_helper.h"

namespace r2lua_test
{
	r2cm::iItem::TitleFuncT PushTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push";
		};
	}
	r2cm::iItem::DoFuncT PushTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( r2lua::Push( lua_state_obj, 777 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( step_helper::LuaViewAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string" ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( step_helper::LuaViewAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );


			return r2cm::eTestEndAction::Pause;
		};
	}

	r2cm::iItem::TitleFuncT GetValueFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetValueFromStack";
		};
	}
	r2cm::iItem::DoFuncT GetValueFromStackTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", true ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( step_helper::LuaViewAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto value = r2lua::GetValueFromStack( lua_state_obj, 1 ) );
				DECLARATION_MAIN( auto value_type = r2lua::GetType( value ) );
				DECLARATION_MAIN( auto num = std::get<r2lua::Number>( value ) );

				std::cout << r2::linefeed;

				std::cout << "value_type : " << static_cast<int>( value_type ) << r2::linefeed;
				std::cout << "num : " << num.GetValue() << r2::linefeed;
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto value = r2lua::GetValueFromStack( lua_state_obj, 2 ) );
				DECLARATION_MAIN( auto value_type = r2lua::GetType( value ) );
				DECLARATION_MAIN( auto num = std::get<r2lua::Number>( value ) );

				std::cout << r2::linefeed;

				std::cout << "value_type : " << static_cast<int>( value_type ) << r2::linefeed;
				std::cout << "num : " << num.GetValue() << r2::linefeed;
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto value = r2lua::GetValueFromStack( lua_state_obj, 3 ) );
				DECLARATION_MAIN( auto value_type = r2lua::GetType( value ) );
				DECLARATION_MAIN( auto str = std::get<r2lua::String>( value ) );

				std::cout << r2::linefeed;

				std::cout << "value_type : " << static_cast<int>( value_type ) << r2::linefeed;
				std::cout << "str : " << str.GetValue() << r2::linefeed;
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto value = r2lua::GetValueFromStack( lua_state_obj, 4 ) );
				DECLARATION_MAIN( auto value_type = r2lua::GetType( value ) );
				DECLARATION_MAIN( auto b = std::get<r2lua::Bool>( value ) );

				std::cout << r2::linefeed;

				std::cout << "value_type : " << static_cast<int>( value_type ) << r2::linefeed;
				std::cout << "b : " << b.GetValue() << r2::linefeed;
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );


			return r2cm::eTestEndAction::Pause;
		};
	}
}