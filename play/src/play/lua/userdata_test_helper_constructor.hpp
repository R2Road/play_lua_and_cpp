#include "lua_header_package.h"
#include "r2tm/r2tm_inspector.hpp"
#include "test_lua_helper.h"

struct Vector2_4_ConstructorTest
{
	Vector2_4_ConstructorTest() : x( 777 ), y( 0 ) {}
	int x;
	int y;

	static int Create( lua_State* l )
	{
		void* d = lua_newuserdata( l, sizeof( Vector2_4_ConstructorTest ) );

		test_lua_helper::PrintAllStack( l );
		OUT_VALUE( ( (Vector2_4_ConstructorTest*)d )->x );

		new ( d ) Vector2_4_ConstructorTest; // <<== Here

		OUT_VALUE( ( (Vector2_4_ConstructorTest*)d )->x );

		return 1;
	};
};