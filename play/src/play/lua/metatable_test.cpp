#include "metatable_test.h"
#include "metatable_test_helper.hpp"

#include "lua_header_package.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test_lua_helper.h"

namespace metatable_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MetaTable : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			LS();

			{
				OUT_NOTE( "MetaTable 을 이용하여 table 에 operator 의 할당이 가능하다." );

				std::cout << r2tm::linefeed;

				OUT_FILE( "src/play/lua/metatable_test_helper.hpp" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_MetatableTest::Create ) );
				PROC_MAIN( lua_setglobal( lua_state_obj, "CreateVector" ) );
			
				std::cout << r2tm::linefeed;

				PROC_MAIN( luaL_newmetatable( lua_state_obj, "VectorMetaTable" ) );
				PROC_MAIN( lua_pushstring( lua_state_obj, "__add" ) );
				PROC_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_MetatableTest::__add ) );
				PROC_MAIN( lua_settable( lua_state_obj, -3 ) );
			}

			LS();

			{
				OUT_FILE( "resources/metatable_test_basic_01.lua" );

				std::cout << r2tm::linefeed;

				PROC_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/metatable_test_basic_01.lua" ) );
			}

			LS();

			{
				PROC_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROC_MAIN( lua_getglobal( lua_state_obj, "v3" ) );
				EXPECT_TRUE( lua_istable( lua_state_obj, -1 ) );

				std::cout << r2tm::linefeed;

				PROC_MAIN( lua_getfield( lua_state_obj, -1, "x" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			LS();

			lua_close( lua_state_obj );

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}