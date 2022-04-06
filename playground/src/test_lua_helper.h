#pragma once

struct lua_State;

namespace test_lua_helper
{
	void PrintStackCount( lua_State* lua_state_obj );
	void PrintTypeName( int type );

	bool DoString( lua_State* lua_state_obj, const char* command_string );
	bool DoString_Silent( lua_State* lua_state_obj, const char* command_string );
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code );

	void PrintStack( lua_State* lua_state_obj, const int stack_index );
	void PrintAllStack( lua_State* lua_state_obj );
	void FillDummyValue2Stack( lua_State* lua_state_obj );
}
