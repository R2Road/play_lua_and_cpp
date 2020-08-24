#pragma once

struct lua_State;

namespace step_helper
{
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code, const char* process_name );
	bool DoString( lua_State* lua_state_obj, const char* command_string );
}
