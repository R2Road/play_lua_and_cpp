#include "pch.h"
#include "stack_test.h"

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
			return "Stack : Push";
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



	r2cm::iItem::TitleFuncT GetTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack : Get";
		};
	}
	r2cm::iItem::DoFuncT GetTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = nullptr );
			PROCESS_SUB( lua_state_obj = luaL_newstate() );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Push( info : lua.h 233 line )" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( const auto stack_count = lua_gettop( lua_state_obj ) );
				std::cout << r2::tab << "stack_count : " << stack_count << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				DECLARATION_MAIN( const auto type_name = luaL_typename( lua_state_obj, 1 ) );
				std::cout << r2::tab << "type_name : " << type_name << r2::linefeed2;

				DECLARATION_MAIN( const auto value = lua_tostring( lua_state_obj, 1 ) );
				std::cout << r2::tab << "value : " << value << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Casting?" << r2::linefeed2;

				DECLARATION_MAIN( const auto type_name = luaL_typename( lua_state_obj, 2 ) );
				std::cout << r2::tab << "type_name : " << type_name << r2::linefeed2;

				DECLARATION_MAIN( const auto value = lua_tostring( lua_state_obj, 2 ) );
				std::cout << r2::tab << "value : " << value << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ 0?" << r2::linefeed2;

				DECLARATION_MAIN( const auto type_name = luaL_typename( lua_state_obj, 0 ) );
				std::cout << r2::tab << "type_name : " << type_name << r2::linefeed2;

				DECLARATION_MAIN( const auto value = lua_tonumber( lua_state_obj, 0 ) );
				std::cout << r2::tab << "value : " << value << r2::linefeed;
			}

			std::cout << r2::split;

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT PrintAllTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stack : Print All";
		};
	}
	r2cm::iItem::DoFuncT PrintAllTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( lua_State* lua_state_obj = nullptr );
			PROCESS_SUB( lua_state_obj = luaL_newstate() );

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

			PROCESS_SUB( lua_close( lua_state_obj ) );

			std::cout << r2::split;


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
				PROCESS_MAIN( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );

				std::cout << r2::linefeed;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
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
				PROCESS_MAIN( test_lua_helper::FillDummyValue2Stack( lua_state_obj ) );
				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, lua_gettop( lua_state_obj ) ) );

				std::cout << r2::linefeed;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_pop( lua_state_obj, 3 ) );

				std::cout << r2::linefeed;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
				std::cout << r2::linefeed << "???????" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "a" ) );

				std::cout << r2::linefeed;

				SHOW_CODE( test_lua_helper::DoString_Silent( lua_state_obj, "a = 15" ) );
				std::cout << "Boom : Don't Do That" << r2::linefeed2;

				PROCESS_SUB( test_lua_helper::PrintAllStack( lua_state_obj ) );
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
				std::cout << r2::tab << "+ Copy : 0 to 1" << r2::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 0, 1 ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( lua_pushstring( lua_state_obj, "dummy_string" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_SUB( lua_pushvalue( lua_state_obj, 2 ) );

				std::cout << r2::linefeed;

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
				std::cout << r2::tab << "+ Copy : 1 to 4 ????" << r2::linefeed2;

				PROCESS_MAIN( lua_copy( lua_state_obj, 1, 4 ) );

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
