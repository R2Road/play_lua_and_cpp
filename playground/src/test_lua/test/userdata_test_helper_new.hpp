#include "lua_header_package.h"
#include "r2cm/r2cm_Inspector.h"
#include "test_lua_helper.h"

struct Vector2_4_NewTest
{
	int x;
	int y;

	void Move( int vx, int vy )
	{
		x += vx;
		y += vy;
	}

	static int Create( lua_State* l )
	{
		// Here
		auto v = (Vector2_4_NewTest*)( lua_newuserdata( l, sizeof( Vector2_4_NewTest ) ) );

		v->x = 1;
		v->y = 2;

		return 1;
	};
};