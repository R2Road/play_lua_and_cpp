#include "pch.h"
#include "step_helper.h"

namespace
{
	void DoTab( const std::size_t tab_count )
	{
		switch( tab_count )
		{
		case 1: std::cout << r2::tab; break;
		case 2: std::cout << r2::tab2; break;
		case 3: std::cout << r2::tab3; break;
		}
	}
}

namespace step_helper
{
	bool LuaErrorCheck( lua_State* lua_state_obj, const int return_code, const char* process_name, const std::size_t tab_count )
	{
		DoTab( tab_count );

		std::cout << "Result" << "[" << process_name << "] : ";

		if( return_code != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "Failed " << r2::linefeed;

			DoTab( tab_count );
			std::cout << error_message << r2::linefeed;

			return false;
		}
		else
		{
			std::cout << "Success" << r2::linefeed;

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

	bool DoString( lua_State* lua_state_obj, const char* command_string, const std::size_t tab_count )
	{
		DoTab( tab_count );

		const int result = luaL_dostring( lua_state_obj, command_string );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "DoString : Failed " << r2::linefeed;
			std::cout << error_message << r2::linefeed;

			return false;
		}
		else
		{
			std::cout << "DoString : Success" << r2::linefeed;

			return true;
		}
	}
	bool LuaDoString_Silent( lua_State* lua_state_obj, const char* command_string, const std::size_t tab_count )
	{
		const int result = luaL_dostring( lua_state_obj, command_string );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			DoTab( tab_count );
			std::cout << "DoString : Failed " << r2::linefeed;
			std::cout << error_message << r2::linefeed;

			return false;
		}
		else
		{
			return true;
		}
	}



	void LuaInsertDummyValueInStack( lua_State* lua_state_obj )
	{
		{
			const char* command = "a = 15";
			step_helper::LuaDoString_Silent( lua_state_obj, command, 3u );
		}

		{
			const char* command = "c = 7";
			step_helper::LuaDoString_Silent( lua_state_obj, command, 3u );
		}

		lua_getglobal( lua_state_obj, "a" );
		lua_getglobal( lua_state_obj, "b" );
		lua_getglobal( lua_state_obj, "c" );
		lua_getglobal( lua_state_obj, "d" );
	}
	void LuaViewAllStack( lua_State* lua_state_obj )
	{
		const int stack_size = lua_gettop( lua_state_obj );

		std::cout << r2::tab << "+ Print Stack" << r2::linefeed2;

		for( int i = 1; stack_size >= i; ++i )
		{
			std::cout << r2::tab << i << r2::tab << luaL_typename( lua_state_obj, i ) << r2::tab;

			switch( lua_type( lua_state_obj, i ) )
			{
			case LUA_TNUMBER:
				std::cout << lua_tonumber( lua_state_obj, i ) << r2::linefeed;
				break;
			case LUA_TSTRING:
				std::cout << lua_tostring( lua_state_obj, i ) << r2::linefeed;
				break;
			case LUA_TBOOLEAN:
				std::cout << ( lua_toboolean( lua_state_obj, i ) ? "true" : "false" ) << r2::linefeed;
				break;
			case LUA_TNIL:
				std::cout << "nil" << r2::linefeed;
				break;
			default:
				std::cout << lua_topointer( lua_state_obj, i ) << r2::linefeed;
				break;
			}
		}

		if( 0 == stack_size )
		{
			std::cout << r2::tab2 << "- Empty" << r2::linefeed;
		}
	}
}