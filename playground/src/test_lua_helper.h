#pragma once

struct lua_State;

namespace step_helper_deprecated
{
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code, const char* process_name, const std::size_t tab_count = 0u );
	void PrintType( const char* name, int type );

	bool LuaDoString( lua_State* lua_state_obj, const char* command_string, const std::size_t tab_count = 0u );
	bool LuaDoString_Silent( lua_State* lua_state_obj, const char* command_string, const std::size_t tab_count = 0u );
}

namespace test_lua_helper
{
	void PrintStackCount( lua_State* lua_state_obj );
	void PrintTypeName( int type );

	bool DoString( lua_State* lua_state_obj, const char* command_string );
	bool DoString_Silent( lua_State* lua_state_obj, const char* command_string );

	void PrintAllStack( lua_State* lua_state_obj );
	void FillDummyValue2Stack( lua_State* lua_state_obj );
}
