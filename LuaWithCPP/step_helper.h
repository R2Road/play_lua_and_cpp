#pragma once

struct lua_State;

namespace step_helper
{
	bool DoString( lua_State* lua_state_obj, const char* command_string );
}
