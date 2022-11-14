#include "metatable_test.h"
#include "metatable_test_helper.hpp"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace metatable_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MetaTable : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			lua_State* lua_state_obj = luaL_newstate();
			luaL_openlibs( lua_state_obj );

			std::cout << r2cm::split;

			{
				OUTPUT_NOTE( "MetaTable 에 operator 의 할당이 가능하다." );

				std::cout << r2cm::linefeed;

				SHOW_FILE( "src/test_lua/test/metatable_test_helper.hpp" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_MetatableTest::Create ) );
				PROCESS_MAIN( lua_setglobal( lua_state_obj, "CreateVector" ) );
			
				std::cout << r2cm::linefeed;

				PROCESS_MAIN( luaL_newmetatable( lua_state_obj, "VectorMetaTable" ) );
				PROCESS_MAIN( lua_pushstring( lua_state_obj, "__add" ) );
				PROCESS_MAIN( lua_pushcfunction( lua_state_obj, Vector2_4_MetatableTest::__add ) );
				PROCESS_MAIN( lua_settable( lua_state_obj, -3 ) );
			}

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/metatable_test_basic_01.lua" );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( test_lua_helper::DoFile_Silent( lua_state_obj, "resources/metatable_test_basic_01.lua" ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( lua_settop( lua_state_obj, 0 ) );
				PROCESS_MAIN( lua_getglobal( lua_state_obj, "v3" ) );
				EXPECT_TRUE( lua_istable( lua_state_obj, -1 ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( lua_getfield( lua_state_obj, -1, "x" ) );
				test_lua_helper::PrintAllStack( lua_state_obj );
			}

			std::cout << r2cm::split;

			lua_close( lua_state_obj );

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}