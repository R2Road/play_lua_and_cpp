#include "userdata_test.h"

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

			DECLARATION_MAIN( struct Vec { int x = 0; int y = 0; } );

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
				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/userdata_test_struct_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Call Lua Function" << r2cm::linefeed2;

				PROCESS_MAIN( lua_getglobal( lua_state_obj, "LUAFunction" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( LUA_OK, lua_pcall( lua_state_obj, 0, LUA_MULTRET, 0 ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );
				DECLARATION_MAIN( Vec* v = (Vec*)lua_touserdata( lua_state_obj, -1 ) );
				OUTPUT_VALUE( v->x );
				OUTPUT_VALUE( v->y );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}