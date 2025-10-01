#include "lua_header_package.h"

#include <vector>

#include "r2tm/r2tm_inspector.hpp"
#include "test_lua_helper.h"

#include "r2/r2_Assert.h"

namespace interaction_test_helper_call_with_closure
{
	struct Sprite;

	struct SpriteManager
	{
		using MySprite = Sprite;

		std::vector<MySprite*> mSprites;
		int mNumberOfMade = 0;

		void Look( MySprite* sprite )
		{
			mSprites.push_back( sprite );
			++mNumberOfMade;
		}
		void Forget( MySprite* sprite )
		{
			int i = 0;
			for( auto& s : mSprites )
			{
				if( s == sprite )
				{
					mSprites.erase( mSprites.begin() + i );
					break;
				}
				++i;
			}
		}
	};

	struct Sprite
	{
		int x;
		int y;

		Sprite() : x( 0 ), y( 0 ) {}
		~Sprite() {}

		static int Create( lua_State* l )
		{
			void* sprite = lua_newuserdata( l, sizeof( Sprite ) );
			new ( sprite ) Sprite();

			luaL_getmetatable( l, "SpriteMetaTable" );
			lua_setmetatable( l, -2 );

			lua_newtable( l );
			lua_setuservalue( l, 1 ); // userdata �� ������ ���� �����Ѵ�.

			SpriteManager* manager = (SpriteManager*)lua_touserdata( l, lua_upvalueindex( 1 ) );
			R2ASSERT( nullptr != manager, "" );
			manager->Look( (Sprite*)sprite );

			return 1;
		};

		static int __gc( lua_State* l )
		{
			auto s = (Sprite*)lua_touserdata( l, -1 );

			SpriteManager* manager = (SpriteManager*)lua_touserdata( l, lua_upvalueindex( 1 ) );
			R2ASSERT( nullptr != manager, "" );
			manager->Forget( s );

			s->~Sprite();

			return 1;
		};

		static int Move( lua_State* l )
		{
			Sprite* s = (Sprite*)lua_touserdata( l, 1 );
			auto vx = (int)lua_tonumber( l, 2 );
			auto vy = (int)lua_tonumber( l, 3 );

			s->x += vx;
			s->y += vy;

			return 0;
		}

		static int Draw( lua_State* l )
		{
			Sprite* s = (Sprite*)lua_touserdata( l, 1 );

			std::cout << "x : " << s->x << "    " "y :" << s->y << "\n";

			return 0;
		}

		static int __index( lua_State* l )
		{
			Sprite* s = (Sprite*)lua_touserdata( l, 1 );

			const char* index_string = lua_tostring( l, 2 );

			if( 0 == std::strcmp( "x", index_string ) )
			{
				lua_pushnumber( l, s->x );
				return 1;
			}

			if( 0 == std::strcmp( "y", index_string ) )
			{
				lua_pushnumber( l, s->y );
				return 1;
			}

			lua_getuservalue( l, 1 );
			lua_pushvalue( l, 2 ); // ���ڷ� �Ѿ�� key ���� ����
			lua_gettable( l, -2 );
			if( !lua_isnil( l, -1 ) )
			{
				return 1;
			}

			lua_getglobal( l, "Sprite" );
			lua_pushstring( l, index_string );
			lua_rawget( l, -2 ); // lua_gettable �� ���������� metamethod �� ������� �ʴ´�.

			return 1;
		}

		static int __newindex( lua_State* l )
		{
			Sprite* s = (Sprite*)lua_touserdata( l, 1 );
			const char* index_string = lua_tostring( l, 2 );

			if( 0 == std::strcmp( "x", index_string ) )
			{
				s->x = (int)lua_tonumber( l, 3 );
				return 0;
			}

			if( 0 == std::strcmp( "y", index_string ) )
			{
				s->y = (int)lua_tonumber( l, 3 );
				return 0;
			}

			lua_getuservalue( l, 1 );
			lua_pushvalue( l, 2 ); // ���ڷ� �Ѿ�� key ���� ����
			lua_pushvalue( l, 3 ); // ���ڷ� �Ѿ�� value ���� ����
			lua_settable( l, -3 );

			return 0;
		}
	};
}