#include "global_test.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

namespace global_test
{
	r2tm::TitleFunctionT Basic_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic 1";
		};
	}
	r2tm::DoFunctionT Basic_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			std::cout << "Note : lua_setglobal 스택 1에 있는 값을 루아의 전역 공간에 추가한다." << r2tm::linefeed;
			std::cout << "Note : lua_getglobal 루아의 전역 공간에서 값을 가져와 스택에 넣는다" << r2tm::linefeed;

			LS();

			{
				std::cout << r2tm::tab << "+ Ready" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_string" ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ SetGlobal" << r2tm::linefeed2;

				PROC_MAIN( lua_setglobal( lua_state_obj, "ds" ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ GetGlobal" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ GetGlobal 은 타입을 반환한다." << r2tm::linefeed2;

				DECL_MAIN( const int type = lua_getglobal( lua_state_obj, "ds" ) );

				LF();

				PROC_MAIN( test_lua_helper::PrintTypeName( type ) );
			}

			LS();


			lua_close( lua_state_obj );


			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Basic_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic 2";
		};
	}
	r2tm::DoFunctionT Basic_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			LS();

			std::cout << "Note : lua_setglobal 로 루아 전역 공간의 값 갱신" << r2tm::linefeed;

			LS();

			{
				std::cout << r2tm::tab << "+ Ready" << r2tm::linefeed2;

				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_string" ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "ds" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				PROC_MAIN( lua_settop( lua_state_obj, 0 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Update" << r2tm::linefeed2;
				
				PROC_MAIN( lua_pushstring( lua_state_obj, "dummy_string 2" ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "ds" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Get" << r2tm::linefeed2;

				PROC_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				LF();

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();



			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}