#include "userdata_test.h"
#include "userdata_test_helper_constructor.hpp"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace userdata_test
{
	r2cm::iItem::TitleFunctionT NewUserData::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : lua_newuserdata";
		};
	}
	r2cm::iItem::DoFunctionT NewUserData::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			std::cout << r2cm::split;

			OUTPUT_NOTE( "lua_newuserdata 를 사용하여 Lua 에서 메모리를 할당한다." );

			std::cout << r2cm::split;

			DECLARATION_MAIN( struct Vec
			{
				int x = 0;
				int y = 0;

				void Move( int vx, int vy )
				{
					x += vx;
					y += vy;
				}
			} );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto cpp_process = []( lua_State* l )->int
				{
					Vec* v = (Vec*)( lua_newuserdata( l, sizeof( Vec ) ) );
					v->x = 1;
					v->y = 2;
					return 1;
				} );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, cpp_process ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPProcess" ) );
			}

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/userdata_test_struct_01.lua" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/userdata_test_struct_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( Vec* v = (Vec*)lua_touserdata( lua_state_obj, -1 ) );
				OUTPUT_VALUE( v->x );
				OUTPUT_VALUE( v->y );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( v->Move( 2, 3 ) );
				OUTPUT_VALUE( v->x );
				OUTPUT_VALUE( v->y );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Constructor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : Constructor";
		};
	}
	r2cm::iItem::DoFunctionT Constructor::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			std::cout << r2cm::split;

			OUTPUT_NOTE( "위치 지정 new 를 활용해서 강제로 생성자를 호출한다." );

			std::cout << r2cm::split;

			{
				SHOW_FILE( "src/test_lua/test/userdata_test_helper_constructor.hpp" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, cpp_process ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CPPProcess" ) );
			}

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/userdata_test_struct_01.lua" );
				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/userdata_test_struct_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( Data* v = (Data*)lua_touserdata( lua_state_obj, -1 ) );
				OUTPUT_VALUE( v->t );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}