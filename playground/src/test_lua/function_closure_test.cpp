#include "pch.h"
#include "function_closure_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

int CPPClosure( lua_State* lua_state_obj )
{
	std::cout << "[CPP] CPPClosure" << r2::linefeed;

	std::cout << "lua_upvalueindex( 1 ) : " << lua_tonumber( lua_state_obj, lua_upvalueindex( 1 ) ) << r2::linefeed;
	std::cout << "lua_upvalueindex( 2 ) : " << lua_tostring( lua_state_obj, lua_upvalueindex( 2 ) ) << r2::linefeed;

	return 0;
}


namespace function_closure_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return " function_closure_test : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );



			std::cout << r2::split;

			std::cout << "Note : cpp 함수와 인자를 묶어 closure 를 만든다." << r2::linefeed;

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const char* command = "function CallCPPClosure()    CPPClosure()    end"; )
				PROCESS_MAIN( test_lua_helper::DoString( lua_state_obj, command ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Make CPP Closure" << r2::linefeed2;

				PROCESS_MAIN( lua_pushnumber( lua_state_obj, 123 ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_text" ) );
				PROCESS_MAIN( lua_pushcclosure( lua_state_obj, CPPClosure, 2 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Register CPP Closure" << r2::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPClosure" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Call Lua Function" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "CallCPPClosure" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2::linefeed;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, 0, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}
}
