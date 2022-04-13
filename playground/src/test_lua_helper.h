#pragma once

struct lua_State;

namespace test_lua_helper
{
	int GetVersion();

	void PrintStackCount( lua_State* lua_state_obj );
	void PrintTypeName( int type );
	void PrintLuaError( lua_State* lua_state_obj );

	bool DoString( lua_State* lua_state_obj, const char* command_string );
	bool DoString_Silent( lua_State* lua_state_obj, const char* command_string );
	bool DoFile( lua_State* lua_state_obj, const char* file_path );
	bool DoFile_Silent( lua_State* lua_state_obj, const char* file_path );
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code );
	bool LuaErrorCheck_Silent( lua_State* lua_state_obj, const int return_code );

	void PrintStack( lua_State* lua_state_obj, const int stack_index );
	void PrintAllStack( lua_State* lua_state_obj );
	void FillDummyValue2Stack( lua_State* lua_state_obj );
}
