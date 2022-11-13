#include "stack_test.h"

#include <string_view>

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

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
	r2cm::iItem::TitleFunctionT PushTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Push";
		};
	}
	r2cm::iItem::DoFunctionT PushTest::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( lua_State* lua_state_obj = luaL_newstate() );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Top" << r2cm::linefeed2;

				OUTPUT_VALUE( lua_gettop( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push( info : lua.h 233 line )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Top" << r2cm::linefeed2;

				OUTPUT_VALUE( lua_gettop( lua_state_obj ) );
			}
			
			std::cout << r2cm::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TypeCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Check : lua_type, lua_typename, lua_isnumber...";
		};
	}
	r2cm::iItem::DoFunctionT TypeCheck::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 0 : Type Check In Stack - lua_is..." << r2cm::linefeed2;

				EXPECT_TRUE( lua_isnil( lua_state_obj, 1 ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, 2 ) );
				EXPECT_TRUE( lua_isinteger( lua_state_obj, 3 ) );
				EXPECT_TRUE( lua_isstring( lua_state_obj, 4 ) );
				EXPECT_TRUE( lua_isstring( lua_state_obj, 5 ) );
				EXPECT_TRUE( lua_iscfunction( lua_state_obj, 6 ) );
				EXPECT_TRUE( lua_isboolean( lua_state_obj, 7 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 1 : Type Check In Stack - lua_type" << r2cm::linefeed2;

				EXPECT_EQ( LUA_TNIL, lua_type( lua_state_obj, 1 ) );
				EXPECT_EQ( LUA_TNUMBER, lua_type( lua_state_obj, 2 ) );
				EXPECT_EQ( LUA_TNUMBER, lua_type( lua_state_obj, 3 ) );
				EXPECT_EQ( LUA_TSTRING, lua_type( lua_state_obj, 4 ) );
				EXPECT_EQ( LUA_TSTRING, lua_type( lua_state_obj, 5 ) );
				EXPECT_EQ( LUA_TFUNCTION, lua_type( lua_state_obj, 6 ) );
				EXPECT_EQ( LUA_TBOOLEAN, lua_type( lua_state_obj, 7 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 2 : Empty Stack" << r2cm::linefeed2;

				DECLARATION_MAIN( const int type = lua_type( lua_state_obj, 8 ) );
				std::cout << "type : " << type << r2cm::linefeed;

				EXPECT_EQ( LUA_TNONE, type );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 3 : Type Name" << r2cm::linefeed2;

				DECLARATION_MAIN( const char* type_name = lua_typename( lua_state_obj, 4 ) );
				std::cout << "type_name : " << type_name << r2cm::linefeed;
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PrintAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Print All";
		};
	}
	r2cm::iItem::DoFunctionT PrintAll::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push( info : lua.h 233 line )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );

				std::cout << r2cm::linefeed;

				std::cout << r2cm::tab << "Stack Count : " << stack_count << r2cm::linefeed;
				for( int i = 1, ri = -stack_count; stack_count >= i; ++i, ++ri )
				{
					std::cout << r2cm::tab << "[" << i << "]" << r2cm::tab << "[" << ri << "]" << r2cm::tab << luaL_typename( lua_state_obj, i ) << r2cm::tab;

					switch( lua_type( lua_state_obj, i ) )
					{
					case LUA_TNUMBER:
						std::cout << lua_tonumber( lua_state_obj, i ) << r2cm::linefeed;
						break;
					case LUA_TSTRING:
						std::cout << lua_tostring( lua_state_obj, i ) << r2cm::linefeed;
						break;
					case LUA_TBOOLEAN:
						std::cout << ( lua_toboolean( lua_state_obj, i ) ? "true" : "false" ) << r2cm::linefeed;
						break;
					case LUA_TNIL:
						std::cout << "nil" << r2cm::linefeed;
						break;
					default:
						std::cout << lua_topointer( lua_state_obj, i ) << r2cm::linefeed;
						break;
					}
				}
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT GetTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Get 1 : lua_to...";
		};
	}
	r2cm::iItem::DoFunctionT GetTest_1::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				DECLARATION_MAIN( const auto s = lua_tostring( lua_state_obj, 1 ) );
				std::cout << r2cm::tab << "s : " << s << r2cm::linefeed2;

				DECLARATION_MAIN( const auto n = lua_tonumber( lua_state_obj, 2 ) );
				std::cout << r2cm::tab << "n : " << n << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Casting?" << r2cm::linefeed2;

				DECLARATION_MAIN( const auto n = lua_tonumber( lua_state_obj, 1 ) );
				std::cout << r2cm::tab << "n : " << n << r2cm::linefeed2;

				DECLARATION_MAIN( const auto s = lua_tostring( lua_state_obj, 2 ) );
				std::cout << r2cm::tab << "s : " << s << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ 0?" << r2cm::linefeed2;

				DECLARATION_MAIN( const auto value = lua_tonumber( lua_state_obj, 0 ) );
				std::cout << r2cm::tab << "value : " << value << r2cm::linefeed;
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT GetTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Get 2 : luaL_check...";
		};
	}
	r2cm::iItem::DoFunctionT GetTest_2::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			std::cout << "Note : Type이 맞지 않으면 프로그램이 강제 종료 된다." << r2cm::linefeed;
			std::cout << "Note : Type의 확인을 먼저 하고 호출하자." << r2cm::linefeed2;
			std::cout << "Note : 빈 Stack을 대상으로 호출해도 강제 종료 된다.( 이게 맞나? )" << r2cm::linefeed;
			std::cout << "Note : 이 상태라면 이 함수들은 쓰지 않는게 맞다고 판단된다." << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123.123 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Test" << r2cm::linefeed2;

				EXPECT_EQ( 7, luaL_checkinteger( lua_state_obj, 1 ) );
				EXPECT_EQ( 123.123, luaL_checknumber( lua_state_obj, 2 ) );
				EXPECT_EQ( std::string_view( "dummy_text" ), luaL_checkstring( lua_state_obj, 3 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Test" << r2cm::linefeed2;

				PROCESS_MAIN( luaL_checkany( lua_state_obj, 1 ) );
				PROCESS_MAIN( luaL_checkany( lua_state_obj, 2 ) );
				PROCESS_MAIN( luaL_checkany( lua_state_obj, 3 ) );
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT SetTop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : lua_settop";
		};
	}
	r2cm::iItem::DoFunctionT SetTop::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			{
				PROCESS_SUB( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Pop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : lua_pop";
		};
	}
	r2cm::iItem::DoFunctionT Pop::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			{
				PROCESS_SUB( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, 2 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, lua_gettop( lua_state_obj ) ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, 3 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
				std::cout << r2cm::linefeed << "???????" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );

				std::cout << r2cm::linefeed;

				OUTPUT_CODE( test_lua_helper::DoString_Silent( lua_state_obj, "a = 15" ) );
				std::cout << "Boom : Don't Do That" << r2cm::linefeed2;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT PushValueTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_pushvalue";
		};
	}
	r2cm::iItem::DoFunctionT PushValueTest::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			{
				std::cout << "Note : 지정된 index의 값을 복사해서 push 한다." << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push: 0 ???" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push: 2 ???" << r2cm::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( lua_settop( lua_state_obj, 0 ) );
				PROCESS_SUB( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_SUB( lua_pushnumber( lua_state_obj, 345 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Push: 1, 0" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CopyTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_copy";
		};
	}
	r2cm::iItem::DoFunctionT CopyTest::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Copy : 0 to 1 ????" << r2cm::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 0, 1 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_SUB( lua_pushstring( lua_state_obj, "dummy_string" ) );
				PROCESS_SUB( lua_pushnil( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Copy : 1 to 2" << r2cm::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 1, 2 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Copy : 2 to 3 ????" << r2cm::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 2, 3 ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT RotateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_rotate";
		};
	}
	r2cm::iItem::DoFunctionT RotateTest::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2cm::split;

			{
				test_lua_helper::FillDummyValue2Stack( lua_state_obj );
				lua_settop( lua_state_obj, lua_gettop( lua_state_obj ) - 2 );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Rotate( 1 to 2 )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 1, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Rotate( 2 to 4 )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 2, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Rotate( 4 to ?? )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 4, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Rotate( 4 to ?? )" << r2cm::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 4, -1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::linefeed;


			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
