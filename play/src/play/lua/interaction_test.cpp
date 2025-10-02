#include "interaction_test.h"
#include "interaction_test_helper_call_with_closure.hpp"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

namespace interaction_test
{
	r2tm::TitleFunctionT CallWithClosure::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Interaction : Call with Closure";
		};
	}
	r2tm::DoFunctionT CallWithClosure::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			std::cout << r2tm::split;

			DECL_MAIN( interaction_test_helper_call_with_closure::SpriteManager manager );

			{
				OUT_NOTE( "metatable 의 __newindex 기능을 활용한 멤버 접근." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/interaction_test_helper_call_with_closure.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushlightuserdata( L, &manager ) );
				PROC_MAIN( lua_pushcclosure( L, interaction_test_helper_call_with_closure::Sprite::Create, 1 ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, interaction_test_helper_call_with_closure::Sprite::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, interaction_test_helper_call_with_closure::Sprite::Draw ) );
				PROC_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );

				PROC_MAIN( lua_pushstring( L, "__gc" ) );
				PROC_MAIN( lua_pushlightuserdata( L, &manager ) );
				PROC_MAIN( lua_pushcclosure( L, interaction_test_helper_call_with_closure::Sprite::__gc, 1 ) );
				PROC_MAIN( lua_settable( L, -3 ) );

				PROC_MAIN( lua_pushstring( L, "__index" ) );
				PROC_MAIN( lua_pushcfunction( L, interaction_test_helper_call_with_closure::Sprite::__index ) );
				PROC_MAIN( lua_settable( L, -3 ) );

				PROC_MAIN( lua_pushstring( L, "__newindex" ) );
				PROC_MAIN( lua_pushcfunction( L, interaction_test_helper_call_with_closure::Sprite::__newindex ) );
				PROC_MAIN( lua_settable( L, -3 ) );
			}

			std::cout << r2tm::split;

			{
				const char* lua_file_path = "resources/interaction_test_call_with_closure_01.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			std::cout << r2tm::split;

			{
				PROC_MAIN( lua_getglobal( L, "temp_x" ) );
				test_lua_helper::PrintAllStack( L );
			}

			std::cout << r2tm::split;

			lua_close( L );
			EXPECT_EQ( 0, manager.mSprites.size() );
			EXPECT_EQ( 2, manager.mNumberOfMade );

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}