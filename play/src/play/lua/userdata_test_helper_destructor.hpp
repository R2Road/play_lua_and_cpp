#include "lua_header_package.h"
#include "r2tm/r2tm_inspector.hpp"
#include "test_lua_helper.h"

struct Vector2_4_DestructorTest
{
	~Vector2_4_DestructorTest()
	{
		OUT_COMMENT( "~Data_4_Destructor()" );
	}
	int x;
	int y;

	static int Create( lua_State* l )
	{
		void* d = lua_newuserdata( l, sizeof( Vector2_4_DestructorTest ) );

		luaL_getmetatable( l, "Vector2MetaTable" ); // <<== Here
		lua_setmetatable( l, -2 );

		return 1;
	};

	static int __gc( lua_State* l )
	{
		Vector2_4_DestructorTest* d = (Vector2_4_DestructorTest*)lua_touserdata( l, -1 );

		d->~Vector2_4_DestructorTest(); // <<== Here

		return 0;
	};
};