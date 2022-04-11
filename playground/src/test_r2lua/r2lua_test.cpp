#include "pch.h"
#include "r2lua_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "r2lua/r2lua.h"
#include "test_lua_helper.h"

namespace r2lua_test
{
	r2cm::iItem::TitleFuncT PushTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Push, r2lua::PushArgs";
		};
	}
	r2cm::iItem::DoFuncT PushTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			{
				PROCESS_MAIN( r2lua::Push( lua_state_obj, 777 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string" ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}

	r2cm::iItem::TitleFuncT GetValueFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::GetValueFromStack";
		};
	}
	r2cm::iItem::DoFuncT GetValueFromStackTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			{
				PROCESS_SUB( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", true ) );
				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 1 ) );
				DECLARATION_MAIN( auto num = std::get<r2lua::Number>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 1, num.GetValue() );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 2 ) );
				DECLARATION_MAIN( auto num = std::get<r2lua::Number>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 3.141592, num.GetValue() );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 3 ) );
				DECLARATION_MAIN( auto str = std::get<r2lua::String>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::String, r2lua::GetType( variant_value ) );
				EXPECT_EQ( "test_string", str.GetValue() );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 4 ) );
				DECLARATION_MAIN( auto b = std::get<r2lua::Bool>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::Bool, r2lua::GetType( variant_value ) );
				EXPECT_EQ( true, b.GetValue() );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}


	r2cm::iItem::TitleFuncT GetValuesFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetValuesFromStack";
		};
	}
	r2cm::iItem::DoFuncT GetValuesFromStackTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			{
				PROCESS_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", false ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			DECLARATION_MAIN( const auto values = r2lua::GetValuesFromStack( lua_state_obj ) );

			std::cout << r2::split;

			int index = 0;
			for( const auto& v : values )
			{
				std::cout << "index : " << index << r2::linefeed;

				DECLARATION_MAIN( auto value_type = r2lua::GetType( v ) );
				switch( value_type )
				{
				case r2lua::Type::Bool:
				{
					DECLARATION_MAIN( const auto& b = r2lua::GetValue<r2lua::Bool>( v ) );
					std::cout << "b : " << b.GetValue() << r2::linefeed;
				}
				break;

				case r2lua::Type::Number:
				{
					DECLARATION_MAIN( const auto& num = r2lua::GetValue<r2lua::Number>( v ) );
					std::cout << "num : " << num.GetValue() << r2::linefeed;
				}
				break;

				case r2lua::Type::String:
				{
					DECLARATION_MAIN( const auto& str = r2lua::GetValue<r2lua::String>( v ) );
					std::cout << "str : " << str.GetValue() << r2::linefeed;
				}
				break;
				}

				++index;
				std::cout << r2::linefeed;
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}