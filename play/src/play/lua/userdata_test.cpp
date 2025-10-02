#include "userdata_test.h"
#include "userdata_n_metatable_test_helper_index_and_newindex.hpp"
#include "userdata_n_metatable_test_helper_field_add_from_lua.hpp"
#include "userdata_n_metatable_test_helper_field_get.hpp"
#include "userdata_n_metatable_test_helper_field_set.hpp"
#include "userdata_n_metatable_test_helper_oop.hpp"
#include "userdata_test_helper_constructor.hpp"
#include "userdata_test_helper_destructor.hpp"
#include "userdata_test_helper_new.hpp"

#include <conio.h>

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

namespace userdata_test
{
	r2tm::TitleFunctionT New::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : lua_newuserdata";
		};
	}
	r2tm::DoFunctionT New::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			LS();

			{
				OUT_NOTE( "lua_newuserdata 를 사용하여 Lua 에서 메모리를 할당한다." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_test_helper_new.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_NewTest::Create ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "CreateVector2" ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_test_01.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, lua_file_path ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );

				std::cout << r2tm::linefeed;

				DECL_MAIN( Vector2_4_NewTest* v = (Vector2_4_NewTest*)lua_touserdata( lua_state_obj, -1 ) );
				OUT_VALUE( v->x );
				OUT_VALUE( v->y );

				std::cout << r2tm::linefeed;

				PROC_MAIN( v->Move( 2, 3 ) );
				OUT_VALUE( v->x );
				OUT_VALUE( v->y );
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Constructor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : Constructor";
		};
	}
	r2tm::DoFunctionT Constructor::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			LS();

			{
				OUT_NOTE( "위치 지정 new 를 활용해서 강제로 생성자를 호출한다." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_test_helper_constructor.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_ConstructorTest::Create ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "CreateVector2" ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_test_01.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, lua_file_path ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );

				std::cout << r2tm::linefeed;

				DECL_MAIN( Vector2_4_ConstructorTest* v = (Vector2_4_ConstructorTest*)lua_touserdata( lua_state_obj, -1 ) );
				OUT_VALUE( v->x );
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Destructor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : Destructor";
		};
	}
	r2tm::DoFunctionT Destructor::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			LS();

			{
				OUT_NOTE( "metatable 을 활용하여 강제로 소멸자를 호출한다." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_test_helper_destructor.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_DestructorTest::Create ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "CreateVector2" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( lua_state_obj, "Vector2MetaTable" ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "__gc" ) );
				PROC_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_DestructorTest::__gc ) );
				PROC_MAIN( lua_settable( lua_state_obj, -3 ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_destructor_01.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, lua_file_path ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_gc( lua_state_obj, LUA_GCCOLLECT ) );
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT OOP_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : OOP 1";
		};
	}
	r2tm::DoFunctionT OOP_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			LS();

			{
				OUT_FILE( "src/play/lua/userdata_n_metatable_test_helper_oop.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_OOP_Test::Create ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_OOP_Test::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_OOP_Test::Draw ) );
				PROC_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_oop_01.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			LS();

			lua_close( L );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT OOP_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : OOP 2";
		};
	}
	r2tm::DoFunctionT OOP_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			LS();

			{
				OUT_NOTE( "metatable 의 __index 기능을 활용한 oop 스러운 코드 작성." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_n_metatable_test_helper_oop.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_OOP_Test::Create ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_OOP_Test::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_OOP_Test::Draw ) );
				PROC_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );
				PROC_MAIN( lua_pushstring( L, "__index" ) );
				PROC_MAIN( lua_pushvalue( L, sprite_table_index ) ); // copy
				PROC_MAIN( lua_settable( L, -3 ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_oop_02.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			LS();

			lua_close( L );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Field_Get::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : Field Get";
		};
	}
	r2tm::DoFunctionT Field_Get::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			LS();

			{
				OUT_NOTE( "metatable 의 __index 기능을 활용한 oop 스러운 코드 작성." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_n_metatable_test_helper_field_get.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Get_Test::Create ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Get_Test::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Get_Test::Draw ) );
				PROC_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );
				PROC_MAIN( lua_pushstring( L, "__index" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Get_Test::__index ) );
				PROC_MAIN( lua_settable( L, -3 ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_field_get_01.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( L, "temp_x" ) );
				test_lua_helper::PrintAllStack( L );
			}

			LS();

			lua_close( L );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Field_Set::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : Field Set";
		};
	}
	r2tm::DoFunctionT Field_Set::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			LS();

			{
				OUT_NOTE( "metatable 의 __newindex 기능을 활용한 멤버 접근." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_n_metatable_test_helper_field_set.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Set_Test::Create ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Set_Test::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Set_Test::Draw ) );
				PROC_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );
				PROC_MAIN( lua_pushstring( L, "__index" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Set_Test::__index ) );
				PROC_MAIN( lua_settable( L, -3 ) );
				PROC_MAIN( lua_pushstring( L, "__newindex" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Set_Test::__newindex ) );
				PROC_MAIN( lua_settable( L, -3 ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_field_set.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( L, "temp_x" ) );
				test_lua_helper::PrintAllStack( L );
			}

			LS();

			lua_close( L );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Index_And_NewIndex::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "__index and __newindex";
		};
	}
	r2tm::DoFunctionT Index_And_NewIndex::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			LS();
			
			OUT_NOTE( "__index 와 __newindex 가 작동하는 시점 확인." );

			LS();

			{
				OUT_FILE( "src/play/lua/userdata_n_metatable_test_helper_index_and_newindex.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Index_N_NewIndex_Test::Create ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Index_N_NewIndex_Test::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );
				PROC_MAIN( lua_pushstring( L, "__index" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Index_N_NewIndex_Test::__index ) );
				PROC_MAIN( lua_settable( L, -3 ) );
				PROC_MAIN( lua_pushstring( L, "__newindex" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Index_N_NewIndex_Test::__newindex ) );
				PROC_MAIN( lua_settable( L, -3 ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_index_and_newindex.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			LS();

			lua_close( L );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Field_AddFromLua::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Field : AddFromLua";
		};
	}
	r2tm::DoFunctionT Field_AddFromLua::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* L = luaL_newstate();
			luaL_openlibs( L );

			LS();

			{
				OUT_NOTE( "metatable 의 __newindex 기능을 활용한 멤버 접근." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/userdata_n_metatable_test_helper_field_add_from_lua.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_newtable( L ) );
				PROC_MAIN( lua_setglobal( L, "Sprite" ) );
				PROC_MAIN( lua_getglobal( L, "Sprite" ) );
				int sprite_table_index = lua_gettop( L );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Add_From_Lua_Test::Create ) );
				PROC_MAIN( lua_setfield( L, -2, "Create" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Add_From_Lua_Test::Move ) );
				PROC_MAIN( lua_setfield( L, -2, "Move" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Add_From_Lua_Test::Draw ) );
				PROC_MAIN( lua_setfield( L, -2, "Draw" ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( L, "SpriteMetaTable" ) );
				PROC_MAIN( lua_pushstring( L, "__index" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Add_From_Lua_Test::__index ) );
				PROC_MAIN( lua_settable( L, -3 ) );
				PROC_MAIN( lua_pushstring( L, "__newindex" ) );
				PROC_MAIN( lua_pushcfunction( L, Sprite_4_Field_Add_From_Lua_Test::__newindex ) );
				PROC_MAIN( lua_settable( L, -3 ) );
			}

			LS();

			{
				const char* lua_file_path = "resources/userdata_n_metatable_test_field_add_from_lua.lua";

				OUT_FILE( lua_file_path );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( L, lua_file_path ) );
			}

			LS();

			{
				PROC_MAIN( lua_getglobal( L, "temp_x" ) );
				test_lua_helper::PrintAllStack( L );
			}

			LS();

			lua_close( L );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}