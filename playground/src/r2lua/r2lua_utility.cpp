#include "pch.h"
#include "r2lua_utility.h"

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
}