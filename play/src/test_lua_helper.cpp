﻿#include "test_lua_helper.h"

#include "lua_header_package.h"

#include "r2tm/r2tm_ostream.hpp"


namespace test_lua_helper
{
	int GetVersion()
	{
		static const int v = []()->int
		{
			lua_State* lua_state_obj = luaL_newstate();
			const auto v = lua_version( lua_state_obj );
			lua_close( lua_state_obj );

			return static_cast<int>( v );
		}();

		return v;
	}

	void PrintStackCount( lua_State* lua_state_obj )
	{
		const int stack_size = lua_gettop( lua_state_obj );
		if( 0 == stack_size )
		{
			std::cout << "Empty" << r2tm::linefeed;
		}
		else
		{
			std::cout << stack_size << r2tm::linefeed;
		}
	}
	void PrintTypeName( int type )
	{
		switch( type )
		{
		case LUA_TNIL:
			std::cout << " is nil" << r2tm::linefeed;
			break;
		case LUA_TBOOLEAN:
			std::cout << " is boolean" << r2tm::linefeed;
			break;
		case LUA_TLIGHTUSERDATA:
			std::cout << " is light userdata" << r2tm::linefeed;
			break;
		case LUA_TNUMBER:
			std::cout << " is number" << r2tm::linefeed;
			break;
		case LUA_TSTRING:
			std::cout << " is string" << r2tm::linefeed;
			break;
		case LUA_TTABLE:
			std::cout << " is table" << r2tm::linefeed;
			break;
		case LUA_TFUNCTION:
			std::cout << " is function" << r2tm::linefeed;
			break;
		case LUA_TUSERDATA:
			std::cout << " is userdata" << r2tm::linefeed;
			break;
		case LUA_TTHREAD:
			std::cout << " is thread" << r2tm::linefeed;
			break;
		case LUA_NUMTYPES:
			std::cout << " is numtypes" << r2tm::linefeed;
			break;

		default:
			std::cout << " is undefined" << r2tm::linefeed;
			break;
		}
	}
	void PrintLuaError( lua_State* lua_state_obj )
	{
		const auto error_message = lua_tostring( lua_state_obj, -1 );
		std::cout << "error message : " << error_message << r2tm::linefeed;
	}

	bool DoString( lua_State* lua_state_obj, const char* command_string )
	{
		return LuaErrorCheck( lua_state_obj, luaL_dostring( lua_state_obj, command_string ) );
	}
	bool DoString_Silent( lua_State* lua_state_obj, const char* command_string )
	{
		return LuaErrorCheck_Silent( lua_state_obj, luaL_dostring( lua_state_obj, command_string ) );
	}
	bool DoFile( lua_State* lua_state_obj, const char* file_path )
	{
		return LuaErrorCheck( lua_state_obj, luaL_dofile( lua_state_obj, file_path ) );
	}
	bool DoFile_Silent( lua_State* lua_state_obj, const char* file_path )
	{
		return LuaErrorCheck_Silent( lua_state_obj, luaL_dofile( lua_state_obj, file_path ) );
	}
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code )
	{
		if( return_code != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );
			std::cout <<"error message : " << error_message << r2tm::linefeed;

			return false;
		}
		else
		{
			std::cout << "Success" << r2tm::linefeed;

			return true;
		}
	}
	bool LuaErrorCheck_Silent( lua_State* lua_state_obj, const int return_code )
	{
		if( return_code != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );
			std::cout << "error message : " << error_message << r2tm::linefeed;

			return false;
		}

		return true;
	}

	void PrintStack( lua_State* lua_state_obj, const int stack_index )
	{
		const int stack_size = lua_gettop( lua_state_obj );

		std::cout << r2tm::tab << "Stack Count : " << stack_size << r2tm::linefeed;
		std::cout << r2tm::tab << "[" << stack_index << "]" << r2tm::tab << "[" << stack_index - ( stack_size + 1 ) << "]" << r2tm::tab << luaL_typename( lua_state_obj, stack_index ) << r2tm::tab;
	}
	void PrintAllStack( lua_State* lua_state_obj )
	{
		const int stack_size = lua_gettop( lua_state_obj );

		std::cout << r2tm::tab << "Stack Count : " << stack_size << r2tm::linefeed;

		if( 0 < stack_size )
		{
			for( int i = 1, ri = -stack_size; stack_size >= i; ++i, ++ri )
			{
				std::cout << r2tm::tab << "[" << i << "]" << r2tm::tab << "[" << ri << "]" << r2tm::tab << luaL_typename( lua_state_obj, i ) << r2tm::tab;

				switch( lua_type( lua_state_obj, i ) )
				{
				case LUA_TNUMBER:
					std::cout << lua_tonumber( lua_state_obj, i ) << r2tm::linefeed;
					break;
				case LUA_TSTRING:
					std::cout << lua_tostring( lua_state_obj, i ) << r2tm::linefeed;
					break;
				case LUA_TBOOLEAN:
					std::cout << ( lua_toboolean( lua_state_obj, i ) ? "true" : "false" ) << r2tm::linefeed;
					break;
				case LUA_TNIL:
					std::cout << "nil" << r2tm::linefeed;
					break;
				default:
					std::cout << lua_topointer( lua_state_obj, i ) << r2tm::linefeed;
					break;
				}
			}
		}
	}
	void FillDummyValue2Stack( lua_State* lua_state_obj )
	{
		{
			const char* command = "a = 15";
			test_lua_helper::DoString_Silent( lua_state_obj, command );
		}

		{
			const char* command = "b = true";
			test_lua_helper::DoString_Silent( lua_state_obj, command );
		}

		{
			const char* command = "c = 'asdf 12345'";
			test_lua_helper::DoString_Silent( lua_state_obj, command );
		}

		{
			const char* command = "d = {}";
			test_lua_helper::DoString_Silent( lua_state_obj, command );
		}

		{
			const char* command = "e = function() end";
			test_lua_helper::DoString_Silent( lua_state_obj, command );
		}

		lua_getglobal( lua_state_obj, "a" );
		lua_getglobal( lua_state_obj, "b" );
		lua_getglobal( lua_state_obj, "c" );
		lua_getglobal( lua_state_obj, "d" );
		lua_getglobal( lua_state_obj, "e" );
		lua_getglobal( lua_state_obj, "f" );
	}
}