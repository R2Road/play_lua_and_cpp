#include "function_closure_test.h"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

int CPPClosure( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure" << r2cm::linefeed;

	std::cout << "lua_upvalueindex( 1 ) : " << lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) ) << r2cm::linefeed;
	std::cout << "lua_upvalueindex( 2 ) : " << lua_tostring( lua_state_obj, lua_upvalueindex( 2 ) ) << r2cm::linefeed;

	return 0;
}
namespace function_closure_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_closure_test : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << "Note : cpp 함수와 인자를 묶어 closure 를 만든다." << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* command = "function CallCPPClosure()    CPPClosure()    end"; )
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Make CPP Closure" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Register CPP Closure" << r2cm::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPClosure" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call Lua Function" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}


int CPPClosure_UpdateUpvalue( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure_UpdateUpvalue" << r2cm::linefeed;

	std::cout << "lua_upvalueindex( 1 ) : " << lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) ) << r2cm::linefeed;

	const auto arg_value = lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) );

	lua_pushnumber( lua_state_obj, arg_value + 1 );
	lua_replace( lua_state_obj, lua_upvalueindex( 1 ) );

	return 0;
}
namespace function_closure_test
{
	r2cm::iItem::TitleFunctionT UpdateUpvalue::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_closure_test : Update Upvalue";
		};
	}
	r2cm::iItem::DoFunctionT UpdateUpvalue::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << "Note : cpp 함수와 묶어놓은 closure의 인자 값을 변경한다." << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* command = "function CallCPPClosure_UpdateUpvalue()    CPPClosure_UpdateUpvalue()    end"; )
				PROCESS_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, command ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure_UpdateUpvalue, 1 ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPClosure_UpdateUpvalue" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call Lua Function" << r2cm::linefeed;

				for( int i = 0; 3 > i; ++i )
				{
					std::cout << r2cm::linefeed;

					PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure_UpdateUpvalue" ) );
					EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				}
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}



int CPPClosure_ArgumentTest( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure_ArgumentTest" << r2cm::linefeed;

	std::cout << "luaL_typename( lua_state_obj, 1 ) : " << luaL_typename( lua_state_obj, 1 ) << r2cm::linefeed;
	std::cout << "lua_tonumber( lua_state_obj, 1 ) : " << lua_tonumber( lua_state_obj, 1 ) << r2cm::linefeed;

	return 0;
}
namespace function_closure_test
{
	r2cm::iItem::TitleFunctionT ArgumentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_closure_test : Argument Test";
		};
	}
	r2cm::iItem::DoFunctionT ArgumentTest::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2cm::split;

			std::cout << "Note : stack 을 통해 인자를 전달하면 작동할까?" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const char* command = "function CallCPPClosure_ArgumentTest()    CPPClosure_ArgumentTest()    end"; )
				PROCESS_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, command ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 111 ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure_ArgumentTest, 1 ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPClosure_ArgumentTest" ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call Lua Function" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure_ArgumentTest" ) );
				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 1, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			std::cout << "Note : 작동 안한다." << r2cm::linefeed;

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}