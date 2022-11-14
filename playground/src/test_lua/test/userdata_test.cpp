#include "userdata_test.h"
#include "userdata_test_helper_constructor.hpp"
#include "userdata_test_helper_destructor.hpp"
#include "userdata_test_helper_new.hpp"

#include <conio.h>

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace userdata_test
{
	r2cm::iItem::TitleFunctionT New::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : lua_newuserdata";
		};
	}
	r2cm::iItem::DoFunctionT New::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "lua_newuserdata 를 사용하여 Lua 에서 메모리를 할당한다." );

				std::cout << r2cm::linefeed;

				SHOW_FILE( "src/test_lua/test/userdata_test_helper_new.hpp" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_NewTest::Create ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CreateVector2" ) );
			}

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/userdata_test_01.lua" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/userdata_test_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( Vector2_4_NewTest* v = (Vector2_4_NewTest*)lua_touserdata( lua_state_obj, -1 ) );
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

			{
				OUTPUT_NOTE( "위치 지정 new 를 활용해서 강제로 생성자를 호출한다." );

				std::cout << r2cm::linefeed;

				SHOW_FILE( "src/test_lua/test/userdata_test_helper_constructor.hpp" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_ConstructorTest::Create ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CreateVector2" ) );
			}

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/userdata_test_01.lua" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/userdata_test_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "vec" ) );
				EXPECT_TRUE( lua_isuserdata( lua_state_obj, -1 ) );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( Vector2_4_ConstructorTest* v = (Vector2_4_ConstructorTest*)lua_touserdata( lua_state_obj, -1 ) );
				OUTPUT_VALUE( v->x );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Destructor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "User Data : Destructor";
		};
	}
	r2cm::iItem::DoFunctionT Destructor::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( lua_State* lua_state_obj = luaL_newstate() );
			luaL_openlibs( lua_state_obj );

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "metatable 을 활용하여 강제로 소멸자를 호출한다." );

				std::cout << r2cm::linefeed;

				SHOW_FILE( "src/test_lua/test/userdata_test_helper_destructor.hpp" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_DestructorTest::Create ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CreateVector2" ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( luaL_newmetatable( lua_state_obj, "Vector2MetaTable" ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "__gc" ) );
				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_DestructorTest::__gc ) );
				PROCESS_MAIN( lua_settable( lua_state_obj, -3 ) );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::linefeed;

				SHOW_FILE( "resources/userdata_test_01.lua" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/userdata_test_01.lua" ) );
			}

			std::cout << r2cm::split;

			PROCESS_MAIN( lua_close( lua_state_obj ) );

			std::cout << r2cm::split;

			_getch();

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}