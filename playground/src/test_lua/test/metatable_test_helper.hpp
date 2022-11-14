#include "lua_header_package.h"
#include "r2cm/r2cm_Inspector.h"
#include "test_lua_helper.h"

struct Vec
{
	int x = 0;
	int y = 0;

	static int CreateVector( lua_State* l )
	{
		lua_newtable( l );

		lua_pushstring( l, "x" );
		lua_pushnumber( l, 0 );
		lua_settable( l, -3 );

		lua_pushstring( l, "y" );
		lua_pushnumber( l, 0 );
		lua_settable( l, -3 );

		luaL_getmetatable( l, "VectorMetaTable" );
		lua_setmetatable( l, -2 );

		return 1;
	}

	static int __add( lua_State* l )
	{
		EXPECT_TRUE( lua_istable( l, 1 ) );
		EXPECT_TRUE( lua_istable( l, 2 ) );

		lua_pushstring( l, "x" );
		lua_gettable( l, 1 );
		lua_Number left_x = lua_tonumber( l, -1 );
		lua_pop( l, 1 );

		lua_pushstring( l, "x" );
		lua_gettable( l, 2 );
		lua_Number right_x = lua_tonumber( l, -1 );
		lua_pop( l, 1 );

		lua_Number ret_x = left_x + right_x;

		CreateVector( l ); // 3 : -3
		lua_pushstring( l, "x" ); // 4 : -2
		lua_pushnumber( l, ret_x ); // 5 : -1

		lua_rawset( l, -3 );

		return 1;
	}
};