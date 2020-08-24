#include "pch.h"

#include "step_helper.h"

namespace step_helper
{
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code, const char* process_name )
	{
		if( return_code != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << process_name << " Failed " << std::endl;
			std::cout << error_message << std::endl;

			return false;
		}
		else
		{
			std::cout << process_name << " Success" << std::endl;

			return true;
		}
	}

	bool DoString( lua_State* lua_state_obj, const char* command_string )
	{
		const int result = luaL_dostring( lua_state_obj, command_string );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "DoString Failed " << std::endl;
			std::cout << error_message << std::endl;

			return false;
		}
		else
		{
			std::cout << "DoString Success" << std::endl;

			return true;
		}
	}
}