#include "pch.h"
#include "stack_test.h"

#include <string_view>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

//
// lua_CFunction : typedef int (*lua_CFunction) (lua_State *L);
//
int cclosure_test_function( lua_State* )
{
	return 0;
}

namespace stack_test
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

			DECLARATION_SUB( lua_State* lua_state_obj = nullptr );
			PROCESS_SUB( lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Top" << r2::linefeed2;

				DECLARATION_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );
				std::cout << r2::tab << "Stack Count : " << stack_count << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push( info : lua.h 233 line )" << r2::linefeed2;

				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Top" << r2::linefeed2;

				DECLARATION_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );
				std::cout << r2::tab << "Stack Count : " << stack_count << r2::linefeed;
			}
			
			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TypeCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Type Check : lua_type, lua_typename, lua_isnumber...";
		};
	}
	r2cm::iItem::DoFuncT TypeCheck::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 0 : Type Check In Stack - lua_is..." << r2::linefeed2;

				EXPECT_TRUE( lua_isnil( lua_state_obj, 1 ) );
				EXPECT_TRUE( lua_isnumber( lua_state_obj, 2 ) );
				EXPECT_TRUE( lua_isinteger( lua_state_obj, 3 ) );
				EXPECT_TRUE( lua_isstring( lua_state_obj, 4 ) );
				EXPECT_TRUE( lua_isstring( lua_state_obj, 5 ) );
				EXPECT_TRUE( lua_iscfunction( lua_state_obj, 6 ) );
				EXPECT_TRUE( lua_isboolean( lua_state_obj, 7 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 1 : Type Check In Stack - lua_type" << r2::linefeed2;

				EXPECT_EQ( LUA_TNIL, lua_type( lua_state_obj, 1 ) );
				EXPECT_EQ( LUA_TNUMBER, lua_type( lua_state_obj, 2 ) );
				EXPECT_EQ( LUA_TNUMBER, lua_type( lua_state_obj, 3 ) );
				EXPECT_EQ( LUA_TSTRING, lua_type( lua_state_obj, 4 ) );
				EXPECT_EQ( LUA_TSTRING, lua_type( lua_state_obj, 5 ) );
				EXPECT_EQ( LUA_TFUNCTION, lua_type( lua_state_obj, 6 ) );
				EXPECT_EQ( LUA_TBOOLEAN, lua_type( lua_state_obj, 7 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 2 : Empty Stack" << r2::linefeed2;

				DECLARATION_MAIN( const int type = lua_type( lua_state_obj, 8 ) );
				std::cout << "type : " << type << r2::linefeed;

				EXPECT_EQ( LUA_TNONE, type );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 3 : Type Name" << r2::linefeed2;

				DECLARATION_MAIN( const char* type_name = lua_typename( lua_state_obj, 4 ) );
				std::cout << "type_name : " << type_name << r2::linefeed;
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PrintAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Print All";
		};
	}
	r2cm::iItem::DoFuncT PrintAll::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push( info : lua.h 233 line )" << r2::linefeed2;

				PROCESS_MAIN( lua_pushnil( lua_state_obj ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 12345.12345 ) );
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushlstring( lua_state_obj, "dummy_text", 3 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, &cclosure_test_function, 0 ) );
				PROCESS_MAIN( lua_pushboolean( lua_state_obj, true ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );

				std::cout << r2::linefeed;

				std::cout << r2::tab << "Stack Count : " << stack_count << r2::linefeed;
				for( int i = 1, ri = -stack_count; stack_count >= i; ++i, ++ri )
				{
					std::cout << r2::tab << "[" << i << "]" << r2::tab << "[" << ri << "]" << r2::tab << luaL_typename( lua_state_obj, i ) << r2::tab;

					switch( lua_type( lua_state_obj, i ) )
					{
					case LUA_TNUMBER:
						std::cout << lua_tonumber( lua_state_obj, i ) << r2::linefeed;
						break;
					case LUA_TSTRING:
						std::cout << lua_tostring( lua_state_obj, i ) << r2::linefeed;
						break;
					case LUA_TBOOLEAN:
						std::cout << ( lua_toboolean( lua_state_obj, i ) ? "true" : "false" ) << r2::linefeed;
						break;
					case LUA_TNIL:
						std::cout << "nil" << r2::linefeed;
						break;
					default:
						std::cout << lua_topointer( lua_state_obj, i ) << r2::linefeed;
						break;
					}
				}
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT GetTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Get 1 : lua_to...";
		};
	}
	r2cm::iItem::DoFuncT GetTest_1::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				DECLARATION_MAIN( const auto s = lua_tostring( lua_state_obj, 1 ) );
				std::cout << r2::tab << "s : " << s << r2::linefeed2;

				DECLARATION_MAIN( const auto n = lua_tonumber( lua_state_obj, 2 ) );
				std::cout << r2::tab << "n : " << n << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Casting?" << r2::linefeed2;

				DECLARATION_MAIN( const auto n = lua_tonumber( lua_state_obj, 1 ) );
				std::cout << r2::tab << "n : " << n << r2::linefeed2;

				DECLARATION_MAIN( const auto s = lua_tostring( lua_state_obj, 2 ) );
				std::cout << r2::tab << "s : " << s << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 0?" << r2::linefeed2;

				DECLARATION_MAIN( const auto value = lua_tonumber( lua_state_obj, 0 ) );
				std::cout << r2::tab << "value : " << value << r2::linefeed;
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT GetTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Get 2 : luaL_check...";
		};
	}
	r2cm::iItem::DoFuncT GetTest_2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			std::cout << "Note : Type이 맞지 않으면 프로그램이 강제 종료 된다." << r2::linefeed;
			std::cout << "Note : Type의 확인을 먼저 하고 호출하자." << r2::linefeed2;
			std::cout << "Note : 빈 Stack을 대상으로 호출해도 강제 종료 된다.( 이게 맞나? )" << r2::linefeed;
			std::cout << "Note : 이 상태라면 이 함수들은 쓰지 않는게 맞다고 판단된다." << r2::linefeed;

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pushinteger( lua_state_obj, 7 ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123.123 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Test" << r2::linefeed2;

				EXPECT_EQ( 7, luaL_checkinteger( lua_state_obj, 1 ) );
				EXPECT_EQ( 123.123, luaL_checknumber( lua_state_obj, 2 ) );
				EXPECT_EQ( std::string_view( "dummy_text" ), luaL_checkstring( lua_state_obj, 3 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Test" << r2::linefeed2;

				PROCESS_MAIN( luaL_checkany( lua_state_obj, 1 ) );
				PROCESS_MAIN( luaL_checkany( lua_state_obj, 2 ) );
				PROCESS_MAIN( luaL_checkany( lua_state_obj, 3 ) );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT SetTop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : lua_settop";
		};
	}
	r2cm::iItem::DoFuncT SetTop::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				PROCESS_SUB( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Pop::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack Clear : lua_pop";
		};
	}
	r2cm::iItem::DoFuncT Pop::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				PROCESS_SUB( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, lua_gettop( lua_state_obj ) ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, 3 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
				std::cout << r2::linefeed << "???????" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );

				std::cout << r2::linefeed;

				SHOW_CODE( test_lua_helper::DoString_Silent( lua_state_obj, "a = 15" ) );
				std::cout << "Boom : Don't Do That" << r2::linefeed2;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PushValueTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_pushvalue";
		};
	}
	r2cm::iItem::DoFuncT PushValueTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				std::cout << "Note : 지정된 index의 값을 복사해서 push 한다." << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push: 0 ???" << r2::linefeed2;

				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push: 2 ???" << r2::linefeed2;

				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( lua_settop( lua_state_obj, 0 ) );
				PROCESS_SUB( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_SUB( lua_pushnumber( lua_state_obj, 345 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push: 1, 0" << r2::linefeed2;

				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				PROCESS_MAIN( lua_pushvalue( lua_state_obj, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT CopyTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_copy";
		};
	}
	r2cm::iItem::DoFuncT CopyTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Copy : 0 to 1 ????" << r2::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 0, 1 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( lua_pushstring( lua_state_obj, "dummy_string" ) );
				PROCESS_SUB( lua_pushnil( lua_state_obj ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Copy : 1 to 2" << r2::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 1, 2 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Copy : 2 to 3 ????" << r2::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 2, 3 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT RotateTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "lua_rotate";
		};
	}
	r2cm::iItem::DoFuncT RotateTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;


			lua_State* lua_state_obj = luaL_newstate();


			std::cout << r2::split;

			{
				test_lua_helper::FillDummyValue2Stack( lua_state_obj );
				lua_settop( lua_state_obj, lua_gettop( lua_state_obj ) - 2 );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Rotate( 1 to 2 )" << r2::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 1, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Rotate( 2 to 4 )" << r2::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 2, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Rotate( 4 to ?? )" << r2::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 4, 1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Rotate( 4 to ?? )" << r2::linefeed2;

				PROCESS_MAIN( lua_rotate( lua_state_obj, 4, -1 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::linefeed;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}
}
