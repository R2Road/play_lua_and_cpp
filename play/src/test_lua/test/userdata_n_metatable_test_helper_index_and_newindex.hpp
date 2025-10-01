#include "lua_header_package.h"
#include "r2tm/r2tm_inspector.hpp"
#include "test_lua_helper.h"

#include "r2/r2_Assert.h"

struct Sprite_4_Index_N_NewIndex_Test
{
	int x;
	int y;

	static int Create( lua_State* l )
	{
		auto s = (Sprite_4_Index_N_NewIndex_Test*)( lua_newuserdata( l, sizeof( Sprite_4_Index_N_NewIndex_Test ) ) );
		s->x = 0;
		s->y = 0;

		luaL_getmetatable( l, "SpriteMetaTable" );
		lua_setmetatable( l, -2 );

		return 1;
	};

	static int Move( lua_State* l )
	{
		std::cout << "Move" "\n";
		return 0;
	}

	static int __index( lua_State* l )
	{
		Sprite_4_Index_N_NewIndex_Test* s = (Sprite_4_Index_N_NewIndex_Test*)lua_touserdata( l, 1 );
		const char* index_string = lua_tostring( l, 2 );

		lua_getglobal( l, "Sprite" );
		lua_pushstring( l, index_string );
		lua_rawget( l, -2 ); // lua_gettable 과 유사하지만 metamethod 를 사용하지 않는다.

		std::cout << "__index" " : " << index_string << "\n";

		return 1;
	}

	static int __newindex( lua_State* l )
	{
		Sprite_4_Index_N_NewIndex_Test* s = (Sprite_4_Index_N_NewIndex_Test*)lua_touserdata( l, 1 );
		const char* index_string = lua_tostring( l, 2 );

		std::cout << "__newindex" " : " << index_string << "\n";
		return 0;
	}
};