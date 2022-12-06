#include "r2lua_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "r2lua/r2lua.h"
#include "test_lua_helper.h"

std::ostream& operator<<( std::ostream& o, const r2lua::eType type )
{
	o.put( static_cast<int>( type ) );
	return ( o );
}

namespace r2lua_test
{
	r2cm::iItem::TitleFunctionT ValueTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Value 1";
		};
	}
	r2cm::iItem::DoFunctionT ValueTest_1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Bool" << r2cm::linefeed2;

				DECLARATION_SUB( const bool primitive_b = true );
				DECLARATION_MAIN( r2lua::Bool b = primitive_b );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Bool, b.GetType() );
				EXPECT_EQ( primitive_b, b.GetValue() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Number" << r2cm::linefeed2;

				DECLARATION_SUB( const double primitive_d = 3.141592 );
				DECLARATION_MAIN( r2lua::Number n = primitive_d );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Number, n.GetType() );
				EXPECT_EQ( primitive_d, n.GetValue() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ String" << r2cm::linefeed2;

				DECLARATION_SUB( const char* primitive_s = "dummy_string" );
				DECLARATION_MAIN( r2lua::String s = primitive_s );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::String, s.GetType() );
				EXPECT_EQ( primitive_s, s.GetValue() );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT ValueTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Value 2";
		};
	}
	r2cm::iItem::DoFunctionT ValueTest_2::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			DECLARATION_SUB( r2lua::Bool b = true );
			DECLARATION_SUB( r2lua::Number n = 3.141592 );
			DECLARATION_SUB( r2lua::String s = "dummy_string" );
			DECLARATION_MAIN( r2lua::Value v; );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Value <> Bool" << r2cm::linefeed2;

				PROCESS_MAIN( v = b );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Bool, r2lua::GetType( v ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( const auto r2lua_value = r2lua::GetValue<r2lua::Bool>( v ) );
				std::cout << r2cm::tab << "real_value.GetValue() : " << r2lua_value.GetValue() << r2cm::linefeed2;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Value <> Number" << r2cm::linefeed2;

				PROCESS_MAIN( v = n );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Number, r2lua::GetType( v ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( const auto r2lua_value = r2lua::GetValue<r2lua::Number>( v ) );
				std::cout << r2cm::tab << "real_value.GetValue() : " << r2lua_value.GetValue() << r2cm::linefeed2;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Value <> String" << r2cm::linefeed2;

				PROCESS_MAIN( v = s );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::String, r2lua::GetType( v ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( const auto r2lua_value = r2lua::GetValue<r2lua::String>( v ) );
				std::cout << r2cm::tab << "real_value.GetValue() : " << r2lua_value.GetValue() << r2cm::linefeed2;
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PushTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Push, r2lua::PushArgs";
		};
	}
	r2cm::iItem::DoFunctionT PushTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			{
				PROCESS_MAIN( r2lua::Push( lua_state_obj, 777 ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string" ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT GetValueFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::GetValueFromStack";
		};
	}
	r2cm::iItem::DoFunctionT GetValueFromStackTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			{
				PROCESS_SUB( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", true ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Number" << r2cm::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 1 ) );
				DECLARATION_MAIN( auto r2lua_value = std::get<r2lua::Number>( variant_value ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 1, r2lua_value.GetValue() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Number" << r2cm::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 2 ) );
				DECLARATION_MAIN( auto r2lua_value = std::get<r2lua::Number>( variant_value ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 3.141592, r2lua_value.GetValue() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ String" << r2cm::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 3 ) );
				DECLARATION_MAIN( auto r2lua_value = std::get<r2lua::String>( variant_value ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::String, r2lua::GetType( variant_value ) );
				EXPECT_EQ( "test_string", r2lua_value.GetValue() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Bool" << r2cm::linefeed2;

				DECLARATION_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 4 ) );
				DECLARATION_MAIN( auto r2lua_value = std::get<r2lua::Bool>( variant_value ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2lua::eType::Bool, r2lua::GetType( variant_value ) );
				EXPECT_EQ( true, r2lua_value.GetValue() );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}


	r2cm::iItem::TitleFunctionT GetValuesFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::GetValuesFromStack";
		};
	}
	r2cm::iItem::DoFunctionT GetValuesFromStackTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			{
				PROCESS_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", false ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto values = r2lua::GetValuesFromStack( lua_state_obj ) );

			std::cout << r2cm::split;

			int index = 0;
			OUTPUT_CODE( for( const auto& v : values ) );
			std::cout << r2cm::linefeed;
			for( const auto& v : values )
			{
				std::cout << "index : " << index << r2cm::linefeed;

				DECLARATION_MAIN( auto value_type = r2lua::GetType( v ) );
				std::cout << r2cm::tab << "type name : " << r2lua::GetTypeName( value_type ) << r2cm::linefeed;
				switch( value_type )
				{
				case r2lua::eType::Bool:
				{
					DECLARATION_MAIN( const auto& b = r2lua::GetValue<r2lua::Bool>( v ) );
					std::cout << r2cm::tab << "b : " << b.GetValue() << r2cm::linefeed;
				}
				break;

				case r2lua::eType::Number:
				{
					DECLARATION_MAIN( const auto& num = r2lua::GetValue<r2lua::Number>( v ) );
					std::cout << r2cm::tab << "num : " << num.GetValue() << r2cm::linefeed;
				}
				break;

				case r2lua::eType::String:
				{
					DECLARATION_MAIN( const auto& str = r2lua::GetValue<r2lua::String>( v ) );
					std::cout << r2cm::tab << "str : " << str.GetValue() << r2cm::linefeed;
				}
				break;
				}

				++index;
				std::cout << r2cm::linefeed;
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CallTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Call";
		};
	}
	r2cm::iItem::DoFunctionT CallTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			

			std::cout << r2cm::split;

			{
				const char* command_4_add_function =
							"function CallTest( arg1, arg2 )"
					"\n"		"print( '[LUA] Call - CallTest - ' .. arg1 .. ', ' .. arg2 )"
					"\n"		"return arg1 + arg2"
					"\n"	"end";

				OUTPUT_CODE( "function CallTest( arg1, arg2 )" );
				OUTPUT_CODE( "	print( '[LUA] Call - CallTest - ' .. arg1 .. ', ' .. arg2 )" );
				OUTPUT_CODE( "	return arg1 + arg2" );
				OUTPUT_CODE( "end" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( luaL_openlibs( lua_state_obj ) );
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command_4_add_function ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( r2lua::Call( lua_state_obj, "CallTest", 3.141592, 7770 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}
}