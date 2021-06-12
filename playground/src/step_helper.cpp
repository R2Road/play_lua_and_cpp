﻿#include "pch.h"

#include "step_helper.h"

namespace step_helper
{
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code, const char* process_name )
	{
		if( return_code != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << process_name << " Failed " << r2::linefeed;
			std::cout << error_message << r2::linefeed;

			return false;
		}
		else
		{
			std::cout << process_name << " Success" << r2::linefeed;

			return true;
		}
	}

	void PrintType( const char* name, int type )
	{
		switch( type )
		{
		case LUA_TNIL:
			std::cout << name << " is nil" << r2::linefeed;
			break;
		case LUA_TBOOLEAN:
			std::cout << name << " is boolean" << r2::linefeed;
			break;
		case LUA_TLIGHTUSERDATA:
			std::cout << name << " is light userdata" << r2::linefeed;
			break;
		case LUA_TNUMBER:
			std::cout << name << " is number" << r2::linefeed;
			break;
		case LUA_TSTRING:
			std::cout << name << " is string" << r2::linefeed;
			break;
		case LUA_TTABLE:
			std::cout << name << " is table" << r2::linefeed;
			break;
		case LUA_TFUNCTION:
			std::cout << name << " is function" << r2::linefeed;
			break;
		case LUA_TUSERDATA:
			std::cout << name << " is userdata" << r2::linefeed;
			break;
		case LUA_TTHREAD:
			std::cout << name << " is thread" << r2::linefeed;
			break;
		case LUA_NUMTYPES:
			std::cout << name << " is numtypes" << r2::linefeed;
			break;

		default:
			std::cout << name << " is undefined" << r2::linefeed;
			break;
		}
	}

	bool DoString( lua_State* lua_state_obj, const char* command_string )
	{
		const int result = luaL_dostring( lua_state_obj, command_string );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "DoString Failed " << r2::linefeed;
			std::cout << error_message << r2::linefeed;

			return false;
		}
		else
		{
			std::cout << "DoString Success" << r2::linefeed;

			return true;
		}
	}
}