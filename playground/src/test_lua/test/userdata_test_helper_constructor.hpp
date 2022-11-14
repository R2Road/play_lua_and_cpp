#include "lua_header_package.h"
#include "r2cm/r2cm_Inspector.h"
#include "test_lua_helper.h"

struct Vector2_4_ConstructorTest
{
	Vector2_4_ConstructorTest() : t( 777 ) {}
	int t;

	static int CreateVector2( lua_State* l )
	{
		void* d = lua_newuserdata( l, sizeof( Vector2_4_ConstructorTest ) );

		test_lua_helper::PrintAllStack( l );
		OUTPUT_VALUE( ( (Vector2_4_ConstructorTest*)d )->t );

		new ( d ) Vector2_4_ConstructorTest; // <<== Here

		OUTPUT_VALUE( ( (Vector2_4_ConstructorTest*)d )->t );

		return 1;
	};
};
