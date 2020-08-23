#include "pch.h"

#include "step_GetGlobal.h"

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
	case LUA_TTABLE	:
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

void step_GetGlobal()
{
	lua_State* lua_state_obj = luaL_newstate();


	//
	// Test 1
	//
	{
		std::cout << "lua_getglobal a" << std::endl;

		//
		// Push Variable "a"
		//
		const int type = lua_getglobal( lua_state_obj, "a" );
		PrintType( "a", type );
	}

	std::cout << std::endl;

	//
	// Test 2
	//
	{
		const std::string command = "b = 7";
		std::cout << "Command : " << command.c_str() << std::endl;

		//
		// Do String
		//
		const int result = luaL_dostring( lua_state_obj, command.c_str() );
		if( result != LUA_OK )
		{
			const auto error_message = lua_tostring( lua_state_obj, -1 );

			std::cout << "Command Failed " << std::endl;
			std::cout << error_message << std::endl;
		}
		else
		{
			std::cout << "Command Success" << std::endl;
		}

		std::cout << "lua_getglobal b" << std::endl;

		//
		// Push Variable "a"
		//
		const int type = lua_getglobal( lua_state_obj, "b" );
		PrintType( "b", type );
	}



	lua_close( lua_state_obj );
}
