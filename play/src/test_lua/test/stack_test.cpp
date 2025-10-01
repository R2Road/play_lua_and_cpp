#include "stack_test.h"

#include <string_view>

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

//
// lua_CFunction : typedef int (*lua_CFunction) (lua_State *L);
//
int cclosure_test_function( lua_State* )
{
	return 0;
}

namespace stack_test
{
	r2tm::TitleFunctionT PushTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push";
		};
	}
	r2tm::DoFunctionT PushTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECL_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Top" );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_gettop( lua_state_obj ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Push( info : lua.h 233 line )" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROC_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROC_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROC_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Top" );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_gettop( lua_state_obj ) );
			}
			
			std::cout << r2tm::split;

			PROC_SUB( lua_close( lua_state_obj ) );

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TypeCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Check : lua_type, lua_isnumber...";
		};
	}
	r2tm::DoFunctionT TypeCheck::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROC_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROC_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROC_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "0 : Type Check In Stack - lua_is..." );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( lua_isnil( lua_state_obj, 1 ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, 2 ) );
				EXPECT_TRUE( lua_isinteger( lua_state_obj, 3 ) );
				EXPECT_TRUE( lua_isstring( lua_state_obj, 4 ) );
				EXPECT_TRUE( lua_isstring( lua_state_obj, 5 ) );
				EXPECT_TRUE( lua_iscfunction( lua_state_obj, 6 ) );
				EXPECT_TRUE( lua_isboolean( lua_state_obj, 7 ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "1 : Type Check In Stack - lua_type" );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( LUA_TNIL, lua_type( lua_state_obj, 1 ) );
				EXPECT_EQ( LUA_TNUMBER, lua_type( lua_state_obj, 2 ) );
				EXPECT_EQ( LUA_TNUMBER, lua_type( lua_state_obj, 3 ) );
				EXPECT_EQ( LUA_TSTRING, lua_type( lua_state_obj, 4 ) );
				EXPECT_EQ( LUA_TSTRING, lua_type( lua_state_obj, 5 ) );
				EXPECT_EQ( LUA_TFUNCTION, lua_type( lua_state_obj, 6 ) );
				EXPECT_EQ( LUA_TBOOLEAN, lua_type( lua_state_obj, 7 ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "2 : Invalid Stack" );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( LUA_TNIL, lua_type( lua_state_obj, 0 ) );
				OUT_VALUE( lua_type( lua_state_obj, 0 ) );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( LUA_TNONE, lua_type( lua_state_obj, 8 ) );
				OUT_VALUE( lua_type( lua_state_obj, 8 ) );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TypeName::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Name : lua_typename...";
		};
	}
	r2tm::DoFunctionT TypeName::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROC_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROC_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROC_MAIN( lua_pushboolean( lua_state_obj, true ) );
				OUT_VALUE( lua_gettop( lua_state_obj ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Type Name" );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 1 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 2 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 3 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 4 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 5 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 6 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 7 ) ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "???" );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 0 ) ) );
				OUT_VALUE( lua_typename( lua_state_obj, lua_type( lua_state_obj, 8 ) ) );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PrintAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Print All";
		};
	}
	r2tm::DoFunctionT PrintAll::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2tm::split;

			{
				OUT_NOTE( "Push( info : lua.h 233 line )" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushnil( lua_state_obj ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROC_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROC_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROC_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2tm::split;

			{
				DECL_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );
				OUT_VALUE( stack_count );

				std::cout << r2tm::linefeed;

				for( int i = 1, ri = -stack_count; stack_count >= i; ++i, ++ri )
				{
					std::cout << r2tm::tab << "[" << i << "]" << r2tm::tab << "[" << ri << "]" << r2tm::tab << luaL_typename( lua_state_obj, i ) << r2tm::tab;

					switch( lua_type( lua_state_obj, i ) )
					{
					case LUA_TNUMBER:
						std::cout << lua_tonumber( lua_state_obj, i ) << r2tm::linefeed;
						break;
					case LUA_TSTRING:
						std::cout << lua_tostring( lua_state_obj, i ) << r2tm::linefeed;
						break;
					case LUA_TBOOLEAN:
						std::cout << ( lua_toboolean( lua_state_obj, i ) ? "true" : "false" ) << r2tm::linefeed;
						break;
					case LUA_TNIL:
						std::cout << "nil" << r2tm::linefeed;
						break;
					default:
						std::cout << lua_topointer( lua_state_obj, i ) << r2tm::linefeed;
						break;
					}
				}
			}

			std::cout << r2tm::split;



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT GetTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Get 1 : lua_to...";
		};
	}
	r2tm::DoFunctionT GetTest_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Get" );

				std::cout << r2tm::linefeed;

				DECL_MAIN( const auto s = lua_tostring( lua_state_obj, 1 ) );
				OUT_VALUE( s );

				DECL_MAIN( const auto n = lua_tonumber( lua_state_obj, 2 ) );
				OUT_VALUE( n );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Casting?" );

				std::cout << r2tm::linefeed;

				DECL_MAIN( const auto n = lua_tonumber( lua_state_obj, 1 ) );
				OUT_VALUE( n );

				DECL_MAIN( const auto s = lua_tostring( lua_state_obj, 2 ) );
				OUT_VALUE( s );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Invalid Index" );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_tonumber( lua_state_obj, 0 ) );
				EXPECT_EQ( nullptr, lua_tostring( lua_state_obj, 0 ) );

				std::cout << r2tm::linefeed;

				OUT_VALUE( lua_tonumber( lua_state_obj, 3 ) );
				EXPECT_EQ( nullptr, lua_tostring( lua_state_obj, 3 ) );
			}

			std::cout << r2tm::split;



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT GetTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Get 2 : luaL_check...";
		};
	}
	r2tm::DoFunctionT GetTest_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			OUT_NOTE( "Type이 맞지 않으면 프로그램이 강제 종료 된다." );
			OUT_NOTE( "Type의 확인을 먼저 하고 호출하자." );
			OUT_NOTE( "빈 Stack을 대상으로 호출해도 강제 종료 된다.( 이게 맞나? )" );
			OUT_NOTE( "이 상태라면 이 함수들은 쓰지 않는게 맞다고 판단된다." );

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 123.123 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Test : luaL_chec..." );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( 7, luaL_checkinteger( lua_state_obj, 1 ) );
				EXPECT_EQ( 123.123, luaL_checknumber( lua_state_obj, 2 ) );
				EXPECT_EQ( std::string_view( "dummy_text" ), luaL_checkstring( lua_state_obj, 3 ) );

				std::cout << r2tm::linefeed;

				OUT_CODE( luaL_checkinteger( lua_state_obj, 3 ) );
				OUT_COMMENT( "위 코드를 수행하면 Type 이 맞지 않아 프로그램이 강제 종료된다." );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Test : luaL_checkany" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_checkany( lua_state_obj, 1 ) );
				PROC_MAIN( luaL_checkany( lua_state_obj, 2 ) );
				PROC_MAIN( luaL_checkany( lua_state_obj, 3 ) );

				std::cout << r2tm::linefeed;

				OUT_CODE( luaL_checkany( lua_state_obj, 4 ) );
				OUT_COMMENT( "위 코드를 수행하면 프로그램이 강제 종료된다." );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT SetTop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : lua_settop";
		};
	}
	r2tm::DoFunctionT SetTop::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				PROC_SUB( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_settop( lua_state_obj, 0 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Pop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : lua_pop";
		};
	}
	r2tm::DoFunctionT Pop::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				PROC_SUB( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pop( lua_state_obj, 2 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pop( lua_state_obj, lua_gettop( lua_state_obj ) ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_pop( lua_state_obj, 3 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
				std::cout << r2tm::linefeed << "???????" << r2tm::linefeed;
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_getglobal( lua_state_obj, "a" ) );

				std::cout << r2tm::linefeed;

				OUT_CODE( test_lua_helper::DoString_Silent( lua_state_obj, "a = 15" ) );
				std::cout << "Boom : Don't Do That" << r2tm::linefeed2;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT PushValueTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_pushvalue";
		};
	}
	r2tm::DoFunctionT PushValueTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				OUT_NOTE( "지정된 index의 값을 복사해서 push 한다." );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Push: 0 ???" << r2tm::linefeed2;

				PROC_MAIN( lua_pushvalue( lua_state_obj, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Push: 2 ???" << r2tm::linefeed2;

				PROC_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROC_MAIN( lua_pushvalue( lua_state_obj, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_SUB( lua_settop( lua_state_obj, 0 ) );
				PROC_SUB( lua_pushnumber( lua_state_obj, 123 ) );
				PROC_SUB( lua_pushnumber( lua_state_obj, 345 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Push: 1, 0" << r2tm::linefeed2;

				PROC_MAIN( lua_pushvalue( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushvalue( lua_state_obj, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CopyTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_copy";
		};
	}
	r2tm::DoFunctionT CopyTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Copy : 0 to 1 ????" << r2tm::linefeed2;

				PROC_MAIN( lua_copy( lua_state_obj, 0, 1 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				PROC_SUB( lua_pushstring( lua_state_obj, "dummy_string" ) );
				PROC_SUB( lua_pushnil( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Copy : 1 to 2" << r2tm::linefeed2;

				PROC_MAIN( lua_copy( lua_state_obj, 1, 2 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Copy : 2 to 3 ????" << r2tm::linefeed2;

				PROC_MAIN( lua_copy( lua_state_obj, 2, 3 ) );

				std::cout << r2tm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT RotateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_rotate";
		};
	}
	r2tm::DoFunctionT RotateTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2tm::split;

			{
				test_lua_helper::FillDummyValue2Stack( lua_state_obj );
				lua_settop( lua_state_obj, lua_gettop( lua_state_obj ) - 2 );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Rotate( 1 ~ 4 를 대상으로 1회 회전 )" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_rotate( lua_state_obj, 1, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Rotate( 1 ~ 4 를 대상으로 1회 역회전 )" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_rotate( lua_state_obj, 1, -1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Rotate( 2 ~ 4 를 대상으로 2회 회전 )" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_rotate( lua_state_obj, 2, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;

			{
				OUT_NOTE( "Rotate( 4 이후에 값이 없으므로 회전이 되지 않는다. )" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_rotate( lua_state_obj, 4, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2tm::split;


			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}
}
