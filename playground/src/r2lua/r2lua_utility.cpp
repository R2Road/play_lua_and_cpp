#include "pch.h"
#include "r2lua_utility.h"

#include <cassert>

namespace r2lua
{
	void Push( lua_State* const lua_state_obj, lua_Number n )
	{
		lua_pushnumber( lua_state_obj, n );
	}
	void Push( lua_State* const lua_state_obj, const char* const str )
	{
		lua_pushstring( lua_state_obj, str );
	}

	r2lua::Value GetValueFromStack( lua_State* const lua_state_obj, int index )
	{
		switch( lua_type( lua_state_obj, index ) )
		{
		case LUA_TNUMBER:
			return r2lua::Number( lua_tonumber( lua_state_obj, index ) );

		case LUA_TSTRING:
			return r2lua::String( lua_tostring( lua_state_obj, index ) );

		default:
			assert( false );
			break;
		}

		return r2lua::Number( 0 );
	}
}