#include "lua_header_package.h"
#include "r2cm/r2cm_Inspector.h"
#include "test_lua_helper.h"

struct Sprite_4_OOP_Test
{
	int x;
	int y;

	static int Create( lua_State* l )
	{
		auto s = (Sprite_4_OOP_Test*)( lua_newuserdata( l, sizeof( Sprite_4_OOP_Test ) ) );
		s->x = 0;
		s->y = 0;

		return 1;
	};

	static int Move( lua_State* l )
	{
		Sprite_4_OOP_Test* s = (Sprite_4_OOP_Test*)lua_touserdata( l, 1 );
		auto vx = (int)lua_tonumber( l, 2 );
		auto vy = (int)lua_tonumber( l, 3 );

		s->x += vx;
		s->y += vy;

		return 0;
	}

	static int Draw( lua_State* l )
	{
		Sprite_4_OOP_Test* s = (Sprite_4_OOP_Test*)lua_touserdata( l, 1 );

		std::cout << "x : " << s->x << "    " "y :" << s->y << "\n";

		return 0;
	}

	static int __gc( lua_State* l )
	{
		return 0;
	}
};