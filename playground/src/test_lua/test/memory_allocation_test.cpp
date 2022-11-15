#include "memory_allocation_test.h"

#include "lua_header_package.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test_lua_helper.h"

namespace memory_allocation_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "memory allocation : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			OUTPUT_NOTE( "luaL_newstate 를 사용하면 lauxlib.c 의 기본 메모리 할당자 l_alloc 가 사용된다." );

			std::cout << r2cm::split;

			{
				SHOW_FILE( "resources/lua_l_alloc.txt" );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( lua_State* lua_state_obj = luaL_newstate() );
				PROCESS_MAIN( lua_close( lua_state_obj ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}
