#include "function_closure_test.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

int CPPClosure( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure" << r2tm::linefeed;

	std::cout << "lua_upvalueindex( 1 ) : " << lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) ) << r2tm::linefeed;
	std::cout << "lua_upvalueindex( 2 ) : " << lua_tostring( lua_state_obj, lua_upvalueindex( 2 ) ) << r2tm::linefeed;

	return 0;
}
namespace function_closure_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_closure_test : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			LS();

			std::cout << "Note : cpp 함수와 인자를 묶어 closure 를 만든다." << r2tm::linefeed;

			LS();

			{
				DECL_MAIN( const char* command = "function CallCPPClosure()    CPPClosure()    end"; )
				PROC_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Make CPP Closure" << r2tm::linefeed2;

				PROC_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Register CPP Closure" << r2tm::linefeed2;

				PROC_MAIN( lua_setglobal( lua_state_obj, "CPPClosure" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call Lua Function" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				LF();

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}


int CPPClosure_UpdateUpvalue( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure_UpdateUpvalue" << r2tm::linefeed;

	std::cout << "lua_upvalueindex( 1 ) : " << lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) ) << r2tm::linefeed;

	const auto arg_value = lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) );

	lua_pushnumber( lua_state_obj, arg_value + 1 );
	lua_replace( lua_state_obj, lua_upvalueindex( 1 ) );

	return 0;
}
namespace function_closure_test
{
	r2tm::TitleFunctionT UpdateUpvalue::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_closure_test : Update Upvalue";
		};
	}
	r2tm::DoFunctionT UpdateUpvalue::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			LS();

			std::cout << "Note : cpp 함수와 묶어놓은 closure의 인자 값을 변경한다." << r2tm::linefeed;

			LS();

			{
				DECL_MAIN( const char* command = "function CallCPPClosure_UpdateUpvalue()    CPPClosure_UpdateUpvalue()    end"; )
				PROC_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, command ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Ready" << r2tm::linefeed2;

				PROC_MAIN( lua_pushnumber( lua_state_obj, 0 ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure_UpdateUpvalue, 1 ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "CPPClosure_UpdateUpvalue" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call Lua Function" << r2tm::linefeed;

				for( int i = 0; 3 > i; ++i )
				{
					LF();

					PROC_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure_UpdateUpvalue" ) );
					EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				}
			}

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}



int CPPClosure_ArgumentTest( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure_ArgumentTest" << r2tm::linefeed;

	std::cout << "luaL_typename( lua_state_obj, 1 ) : " << luaL_typename( lua_state_obj, 1 ) << r2tm::linefeed;
	std::cout << "lua_tonumber( lua_state_obj, 1 ) : " << lua_tonumber( lua_state_obj, 1 ) << r2tm::linefeed;

	return 0;
}
namespace function_closure_test
{
	r2tm::TitleFunctionT ArgumentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "function_closure_test : Argument Test";
		};
	}
	r2tm::DoFunctionT ArgumentTest::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			LS();

			std::cout << "Note : stack 을 통해 인자를 전달하면 작동할까?" << r2tm::linefeed;

			LS();

			{
				DECL_MAIN( const char* command = "function CallCPPClosure_ArgumentTest()    CPPClosure_ArgumentTest()    end"; )
				PROC_MAIN( test_lua_helper::DoString_Silent( lua_state_obj, command ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Ready" << r2tm::linefeed2;

				PROC_MAIN( lua_pushnumber( lua_state_obj, 111 ) );
				PROC_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure_ArgumentTest, 1 ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "CPPClosure_ArgumentTest" ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Call Lua Function" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure_ArgumentTest" ) );
				PROC_MAIN( lua_pushnumber( lua_state_obj, 777 ) );

				LF();

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 1, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			std::cout << "Note : 작동 안한다." << r2tm::linefeed;

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}