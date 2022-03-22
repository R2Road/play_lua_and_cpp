#pragma once

//
// # REF
// CppCon 2017: Andreas Weis “Howling at the Moon: Lua for C++ Programmers”
// https://www.youtube.com/watch?v=pfwHCiP1HFM
//

struct lua_State;

namespace r2lua
{
	void Push( lua_State* const lua_state_obj, lua_Number n );
	void Push( lua_State* const lua_state_obj, const char* const str );

	template<typename... Args>
	void PushArgs( lua_State* const lua_state_obj, Args... args )
	{
		( Push( lua_state_obj, args ), ... );
	}
}
