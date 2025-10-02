#include "play_r2lua.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "r2lua/r2lua.h"
#include "test_lua_helper.h"

std::ostream& operator<<( std::ostream& o, const r2lua::eType type )
{
	o.put( static_cast<int>( type ) );
	return ( o );
}

namespace play_r2lua
{
	r2tm::TitleFunctionT Type_Bool::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type : Bool";
		};
	}
	r2tm::DoFunctionT Type_Bool::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			{
				OUT_SUBJECT( "기본 생성자" );

				LF();

				DECL_MAIN( r2lua::Bool b );

				LF();

				OUT_SIZE( b );

				LF();

				OUT_BINARY( b );

				LF();

				EXPECT_EQ( r2lua::eType::Bool, b.GetType() );
				EXPECT_EQ( false, b.GetValue() );
			}

			SS();

			{
				OUT_SUBJECT( "인자를 받는 생성자" );

				LF();

				DECL_SUB( constexpr const bool primitive_b = true );
				DECL_MAIN( r2lua::Bool b = primitive_b );

				LF();

				OUT_SIZE( b );

				LF();

				OUT_BINARY( b );

				LF();

				EXPECT_EQ( r2lua::eType::Bool, b.GetType() );
				EXPECT_EQ( primitive_b, b.GetValue() );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Type_Number::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type : Number";
		};
	}
	r2tm::DoFunctionT Type_Number::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			{
				OUT_SUBJECT( "기본 생성자" );

				LF();

				DECL_MAIN( r2lua::Number n );

				LF();

				OUT_SIZE( n );

				LF();

				OUT_BINARY( n );

				LF();

				EXPECT_EQ( r2lua::eType::Number, n.GetType() );
				EXPECT_EQ( -1, n.GetValue() );
			}

			SS();

			{
				OUT_SUBJECT( "인자를 받는 생성자" );

				LF();

				DECL_SUB( constexpr const double primitive_d = 3.141592 );
				DECL_MAIN( r2lua::Number n = primitive_d );

				LF();

				OUT_SIZE( n );

				LF();

				OUT_BINARY( n );

				LF();

				EXPECT_EQ( r2lua::eType::Number, n.GetType() );
				EXPECT_EQ( primitive_d, n.GetValue() );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Type_String::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type : String";
		};
	}
	r2tm::DoFunctionT Type_String::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			{
				OUT_SUBJECT( "기본 생성자" );

				LF();

				DECL_MAIN( r2lua::String s );

				LF();

				EXPECT_EQ( r2lua::eType::String, s.GetType() );
				EXPECT_EQ( r2lua::String::InvalidString, s.GetValue() );

				LF();

				OUT_SIZE( s );

				LF();

				OUT_BINARY( s );

				LF();

				OUT_VALUE( r2lua::String::InvalidString );
			}

			SS();

			{
				OUT_SUBJECT( "인자를 받는 생성자" );

				LF();

				DECL_SUB( constexpr const char* primitive_s = "dummy_string" );
				DECL_MAIN( r2lua::String s = primitive_s );

				LF();

				OUT_SIZE( s );

				LF();

				OUT_BINARY( s );

				LF();

				EXPECT_EQ( r2lua::eType::String, s.GetType() );
				EXPECT_EQ( primitive_s, s.GetValue() );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Value::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Value";
		};
	}
	r2tm::DoFunctionT Value::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			{
				DECL_MAIN( r2lua::Value v; );

				SS();

				{
					OUT_SIZE( v );

					LF();

					OUT_BINARY( v );
				}

				SS();

				EXPECT_EQ( r2lua::eType::Bool, r2lua::GetType( v ) );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Value_2_Bool::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Value 2 Bool";
		};
	}
	r2tm::DoFunctionT Value_2_Bool::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			DECL_SUB( r2lua::Bool b = true );

			SS();

			DECL_MAIN( r2lua::Value v; );

			LS();

			{
				OUT_SUBJECT( "Value > Bool" );

				LF();

				PROC_MAIN( v = b );

				SS();

				{
					OUT_SIZE( v );

					LF();

					OUT_BINARY( v );
				}

				SS();

				EXPECT_EQ( r2lua::eType::Bool, r2lua::GetType( v ) );

				LF();

				DECL_MAIN( const auto r2lua_value = r2lua::GetValue<r2lua::Bool>( v ) );
				EXPECT_EQ( b.GetValue(), r2lua_value.GetValue() );

				LF();

				OUT_VALUE( r2lua_value.GetValue() );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Value_2_Number::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Value 2 Number";
		};
	}
	r2tm::DoFunctionT Value_2_Number::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			DECL_SUB( r2lua::Number n = 3.141592 );

			SS();

			DECL_MAIN( r2lua::Value v; );

			LS();

			{
				OUT_SUBJECT( "Value > Number" );

				LF();

				PROC_MAIN( v = n );

				SS();

				{
					OUT_SIZE( v );

					LF();

					OUT_BINARY( v );
				}

				SS();

				EXPECT_EQ( r2lua::eType::Number, r2lua::GetType( v ) );

				LF();

				DECL_MAIN( const auto r2lua_value = r2lua::GetValue<r2lua::Number>( v ) );
				EXPECT_EQ( n.GetValue(), r2lua_value.GetValue() );

				LF();

				OUT_VALUE( r2lua_value.GetValue() );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Value_2_String::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Value 2 String";
		};
	}
	r2tm::DoFunctionT Value_2_String::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			LS();

			DECL_SUB( r2lua::String s = "dummy_string" );

			SS();

			DECL_MAIN( r2lua::Value v; );

			LS();

			{
				OUT_SUBJECT( "Value > String" );

				LF();

				PROC_MAIN( v = s );

				SS();

				{
					OUT_SIZE( v );

					LF();

					OUT_BINARY( v );
				}

				SS();

				EXPECT_EQ( r2lua::eType::String, r2lua::GetType( v ) );

				LF();

				DECL_MAIN( const auto r2lua_value = r2lua::GetValue<r2lua::String>( v ) );
				EXPECT_EQ( s.GetValue(), r2lua_value.GetValue() );

				LF();

				OUT_VALUE( r2lua_value.GetValue() );
			}

			LS();

			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PushTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Push, r2lua::PushArgs";
		};
	}
	r2tm::DoFunctionT PushTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			{
				PROC_MAIN( r2lua::Push( lua_state_obj, 777 ) );

				LF();

				PROC_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			LS();

			{
				PROC_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string" ) );

				LF();

				PROC_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT GetValueFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::GetValueFromStack";
		};
	}
	r2tm::DoFunctionT GetValueFromStackTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			{
				PROC_SUB( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", true ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Number" << r2tm::linefeed2;

				DECL_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 1 ) );
				DECL_MAIN( auto r2lua_value = std::get<r2lua::Number>( variant_value ) );

				LF();

				EXPECT_EQ( r2lua::eType::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 1, r2lua_value.GetValue() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Number" << r2tm::linefeed2;

				DECL_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 2 ) );
				DECL_MAIN( auto r2lua_value = std::get<r2lua::Number>( variant_value ) );

				LF();

				EXPECT_EQ( r2lua::eType::Number, r2lua::GetType( variant_value ) );
				EXPECT_EQ( 3.141592, r2lua_value.GetValue() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ String" << r2tm::linefeed2;

				DECL_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 3 ) );
				DECL_MAIN( auto r2lua_value = std::get<r2lua::String>( variant_value ) );

				LF();

				EXPECT_EQ( r2lua::eType::String, r2lua::GetType( variant_value ) );
				EXPECT_EQ( "test_string", r2lua_value.GetValue() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Bool" << r2tm::linefeed2;

				DECL_MAIN( auto variant_value = r2lua::GetValueFromStack( lua_state_obj, 4 ) );
				DECL_MAIN( auto r2lua_value = std::get<r2lua::Bool>( variant_value ) );

				LF();

				EXPECT_EQ( r2lua::eType::Bool, r2lua::GetType( variant_value ) );
				EXPECT_EQ( true, r2lua_value.GetValue() );
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}


	r2tm::TitleFunctionT GetValuesFromStackTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::GetValuesFromStack";
		};
	}
	r2tm::DoFunctionT GetValuesFromStackTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			{
				PROC_MAIN( r2lua::PushArgs( lua_state_obj, 1, 3.141592, "test_string", false ) );

				LF();

				PROC_MAIN( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			LS();

			DECL_MAIN( const auto values = r2lua::GetValuesFromStack( lua_state_obj ) );

			LS();

			int index = 0;
			OUT_CODE( for( const auto& v : values ) );
			LF();
			for( const auto& v : values )
			{
				std::cout << "index : " << index << r2tm::linefeed;

				DECL_MAIN( auto value_type = r2lua::GetType( v ) );
				std::cout << r2tm::tab << "type name : " << r2lua::GetTypeName( value_type ) << r2tm::linefeed;
				switch( value_type )
				{
				case r2lua::eType::Bool:
				{
					DECL_MAIN( const auto& b = r2lua::GetValue<r2lua::Bool>( v ) );
					std::cout << r2tm::tab << "b : " << b.GetValue() << r2tm::linefeed;
				}
				break;

				case r2lua::eType::Number:
				{
					DECL_MAIN( const auto& num = r2lua::GetValue<r2lua::Number>( v ) );
					std::cout << r2tm::tab << "num : " << num.GetValue() << r2tm::linefeed;
				}
				break;

				case r2lua::eType::String:
				{
					DECL_MAIN( const auto& str = r2lua::GetValue<r2lua::String>( v ) );
					std::cout << r2tm::tab << "str : " << str.GetValue() << r2tm::linefeed;
				}
				break;
				}

				++index;
				LF();
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CallTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "r2lua::Call";
		};
	}
	r2tm::DoFunctionT CallTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();

			

			LS();

			{
				const char* command_4_add_function =
							"function CallTest( arg1, arg2 )"
					"\n"		"print( '[LUA] Call - CallTest - ' .. arg1 .. ', ' .. arg2 )"
					"\n"		"return arg1 + arg2"
					"\n"	"end";

				OUT_CODE( "function CallTest( arg1, arg2 )" );
				OUT_CODE( "	print( '[LUA] Call - CallTest - ' .. arg1 .. ', ' .. arg2 )" );
				OUT_CODE( "	return arg1 + arg2" );
				OUT_CODE( "end" );

				LF();

				PROC_MAIN( luaL_openlibs( lua_state_obj ) );
				PROC_MAIN( test_lua_helper::DoString( lua_state_obj, command_4_add_function ) );
			}

			LS();

			{
				PROC_MAIN( r2lua::Call( lua_state_obj, "CallTest", 3.141592, 7770 ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}
}