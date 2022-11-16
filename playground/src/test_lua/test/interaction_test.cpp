#include "interaction_test.h"
#include "interaction_test_helper_call_with_closure.hpp"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace interaction_test
{
	r2cm::iItem::TitleFunctionT CallWithClosure::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Interaction : Call with Closure";
		};
	}
	r2cm::iItem::DoFunctionT CallWithClosure::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			std::cout << r2cm::split;

			DECLARATION_MAIN( SpriteManager manager );

			{
				OUTPUT_NOTE( "metatable 의 __newindex 기능을 활용한 멤버 접근." );

				std::cout << r2cm::linefeed;

				SHOW_FILE( "src/test_lua/test/interaction_test_helper_call_with_closure.hpp" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_newtable( L ) );
				PROCESS_MAIN( lua_setglobal( L, "Sprite" ) );
				PROCESS_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushlightuserdata( L, &manager ) );
				PROCESS_MAIN( lua_pushcclosure( L, Sprite_4_Call_With_Closure::Create, 1 ) );
				PROCESS_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( L, Sprite_4_Call_With_Closure::Move ) );
				PROCESS_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( L, Sprite_4_Call_With_Closure::Draw ) );
				PROCESS_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );

				PROCESS_MAIN( lua_pushstring( L, "__gc" ) );
				PROCESS_MAIN( lua_pushlightuserdata( L, &manager ) );
				PROCESS_MAIN( lua_pushcclosure( L, Sprite_4_Call_With_Closure::__gc, 1 ) );
				PROCESS_MAIN( lua_settable( L, -3 ) );

				PROCESS_MAIN( lua_pushstring( L, "__index" ) );
				PROCESS_MAIN( lua_pushcfunction( L, Sprite_4_Call_With_Closure::__index ) );
				PROCESS_MAIN( lua_settable( L, -3 ) );

				PROCESS_MAIN( lua_pushstring( L, "__newindex" ) );
				PROCESS_MAIN( lua_pushcfunction( L, Sprite_4_Call_With_Closure::__newindex ) );
				PROCESS_MAIN( lua_settable( L, -3 ) );
			}

			std::cout << r2cm::split;

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_field_add_from_lua.lua";

				SHOW_FILE( lua_file_path );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( L, "temp_x" ) );
				test_lua_helper::PrintAllStack( L );
			}

			std::cout << r2cm::split;

			lua_close( L );
			EXPECT_EQ( 0, manager.number_of_sprites );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}