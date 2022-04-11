#include "pch.h"
#include "r2lua_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "r2lua/r2lua.h"
#include "test_lua_helper.h"

namespace r2lua_test
{
	r2cm::iItem::TitleFuncT ValueTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Value";
		};
	}
	r2cm::iItem::DoFuncT ValueTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			std::cout << r2::tab << "+ 정의" << r2::linefeed2;

			DECLARATION_MAIN( r2lua::Bool b = true );
			DECLARATION_MAIN( r2lua::Number n = 3.141592 );
			DECLARATION_MAIN( r2lua::String s = "dummy_string" );
			DECLARATION_MAIN( r2lua::Value v; );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Value <> Bool" << r2::linefeed2;

				PROCESS_MAIN( v = b );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const auto real_type = r2lua::GetType( v ) );
				std::cout << r2::tab << "static_cast<int>( real_type ) : " << static_cast<int>( real_type ) << r2::linefeed2;

				DECLARATION_MAIN( const auto real_value = r2lua::GetValue<r2lua::Bool>( v ) );
				std::cout << r2::tab << "real_value.GetValue() : " << real_value.GetValue() << r2::linefeed2;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Value <> Number" << r2::linefeed2;

				PROCESS_MAIN( v = n );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const auto real_type = r2lua::GetType( v ) );
				std::cout << r2::tab << "static_cast<int>( real_type ) : " << static_cast<int>( real_type ) << r2::linefeed2;

				DECLARATION_MAIN( const auto real_value = r2lua::GetValue<r2lua::Number>( v ) );
				std::cout << r2::tab << "real_value.GetValue() : " << real_value.GetValue() << r2::linefeed2;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Value <> String" << r2::linefeed2;

				PROCESS_MAIN( v = s );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const auto real_type = r2lua::GetType( v ) );
				std::cout << r2::tab << "static_cast<int>( real_type ) : " << static_cast<int>( real_type ) << r2::linefeed2;

				DECLARATION_MAIN( const auto real_value = r2lua::GetValue<r2lua::String>( v ) );
				std::cout << r2::tab << "real_value.GetValue() : " << real_value.GetValue() << r2::linefeed2;
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



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
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Number" << r2::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 1 ) );
				DECLARATION_MAIN( auto real_value = std::get<r2lua::Number>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 1, real_value.GetValue() );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Number" << r2::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 2 ) );
				DECLARATION_MAIN( auto real_value = std::get<r2lua::Number>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 3.141592, real_value.GetValue() );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ String" << r2::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 3 ) );
				DECLARATION_MAIN( auto real_value = std::get<r2lua::String>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::String, r2lua::GetType( variant_value ) );
				EXPECT_EQ( "test_string", real_value.GetValue() );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Bool" << r2::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 4 ) );
				DECLARATION_MAIN( auto real_value = std::get<r2lua::Bool>( variant_value ) );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2lua::Type::Bool, r2lua::GetType( variant_value ) );
				EXPECT_EQ( true, real_value.GetValue() );
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
			SHOW_CODE( for( const auto& v : values ) );
			std::cout << r2::linefeed;
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