#pragma once

struct lua_State;

namespace step_helper
{
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code, const char* process_name, const std::size_t tab_count = 0u );
	void PrintType( const char* name, int type );

	bool DoString( lua_State* lua_state_obj, const char* command_string, const std::size_t tab_count = 0u );
	bool LuaDoString_Silent( lua_State* lua_state_obj, const char* command_string, const std::size_t tab_count = 0u );

	void LuaViewAllStack( lua_State* lua_state_obj );
}
