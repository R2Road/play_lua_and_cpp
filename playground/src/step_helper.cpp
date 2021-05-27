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

	void PrintType( const char* name, int type )
	{
		switch( type )
		{
		case LUA_TNIL:
			std::cout << name << " is nil" << std::endl;
			break;
		case LUA_TBOOLEAN:
			std::cout << name << " is boolean" << std::endl;
			break;
		case LUA_TLIGHTUSERDATA:
			std::cout << name << " is light userdata" << std::endl;
			break;
		case LUA_TNUMBER:
			std::cout << name << " is number" << std::endl;
			break;
		case LUA_TSTRING:
			std::cout << name << " is string" << std::endl;
			break;
		case LUA_TTABLE:
			std::cout << name << " is table" << std::endl;
			break;
		case LUA_TFUNCTION:
			std::cout << name << " is function" << std::endl;
			break;
		case LUA_TUSERDATA:
			std::cout << name << " is userdata" << std::endl;
			break;
		case LUA_TTHREAD:
			std::cout << name << " is thread" << std::endl;
			break;
		case LUA_NUMTYPES:
			std::cout << name << " is numtypes" << std::endl;
			break;

		default:
			std::cout << name << " is undefined" << std::endl;
			break;
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