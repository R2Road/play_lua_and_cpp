#include "global_test.h"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace global_test
{
	r2cm::iItem::TitleFunctionT Basic_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic 1";
		};
	}
	r2cm::iItem::DoFunctionT Basic_1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			std::cout << "Note : lua_setglobal 스택 1에 있는 값을 루아의 전역 공간에 추가한다." << r2cm::linefeed;
			std::cout << "Note : lua_getglobal 루아의 전역 공간에서 값을 가져와 스택에 넣는다" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_string" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ SetGlobal" << r2cm::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "ds" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ GetGlobal" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ GetGlobal 은 타입을 반환한다." << r2cm::linefeed2;

				DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintTypeName( type ) );
			}

			std::cout << r2cm::split;


			lua_close( lua_state_obj );


			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Basic_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic 2";
		};
	}
	r2cm::iItem::DoFunctionT Basic_2::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2cm::split;

			std::cout << "Note : lua_setglobal 로 루아 전역 공간의 값 갱신" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Ready" << r2cm::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_string" ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "ds" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Update" << r2cm::linefeed2;
				
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_string 2" ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "ds" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Get" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2cm::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;



			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}