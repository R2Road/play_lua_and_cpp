#include "pch.h"
#include "global_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

namespace global_test
{
	r2cm::iItem::TitleFuncT Basic_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic 1";
		};
	}
	r2cm::iItem::DoFuncT Basic_1::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			std::cout << "Note : lua_setglobal 스택 1에 있는 값을 루아의 전역 공간에 추가한다." << r2::linefeed;
			std::cout << "Note : lua_getglobal 루아의 전역 공간에서 값을 가져와 스택에 넣는다" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_string" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ SetGlobal" << r2::linefeed2;

				PROCESS_MAIN( lua_setglobal( lua_state_obj, "ds" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ GetGlobal" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ GetGlobal 은 타입을 반환한다." << r2::linefeed2;

				DECLARATION_MAIN( const int type = lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( test_lua_helper::PrintTypeName( type ) );
			}

			std::cout << r2::split;


			lua_close( lua_state_obj );


			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Basic_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic 2";
		};
	}
	r2cm::iItem::DoFuncT Basic_2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			lua_State* lua_state_obj = luaL_newstate();



			std::cout << r2::split;

			std::cout << "Note : lua_setglobal 로 루아 전역 공간의 값 갱신" << r2::linefeed;

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Ready" << r2::linefeed2;

				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_string" ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "ds" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Update" << r2::linefeed2;
				
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "dummy_string 2" ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "ds" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Get" << r2::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "ds" ) );

				std::cout << r2::linefeed;

				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2::split;



			lua_close( lua_state_obj );

			return r2cm::eTestEndAction::Pause;
		};
	}
}