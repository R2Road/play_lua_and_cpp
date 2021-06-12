#include "pch.h"

#include "step_helper.h"
#include "step_DoFile.h"

namespace step
{
	void DoFile()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << r2::linefeed;
		luaL_openlibs( lua_state_obj );

		std::cout << r2::linefeed;

		//
		// Test x 0
		//
		{
			std::cout << "# Test 0" << r2::linefeed;

			const int result = luaL_dofile( lua_state_obj, "resources/step_DoFile_00.lua" );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "DoFile Failed" << r2::linefeed;
				std::cout << error_message << r2::linefeed;
			}
			else
			{
				std::cout << "DoFile Success" << r2::linefeed;
			}

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << r2::linefeed;
			}
		}

		std::cout << r2::linefeed;

		//
		// Test x 1
		//
		{
			std::cout << "# Test 1" << r2::linefeed;

			const int result = luaL_dofile( lua_state_obj, "resources/step_DoFile_01.lua" );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "DoFile Failed" << r2::linefeed;
				std::cout << error_message << r2::linefeed;
			}
			else
			{
				std::cout << "DoFile Success" << r2::linefeed;
			}

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << r2::linefeed;
			}
		}

		std::cout << r2::linefeed;

		//
		// Test x 2
		//
		{
			std::cout << "# Test 2" << r2::linefeed;

			const int result = luaL_dofile( lua_state_obj, "resources/step_DoFile_02.lua" );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "DoFile Failed" << r2::linefeed;
				std::cout << error_message << r2::linefeed;
			}
			else
			{
				std::cout << "DoFile Success" << r2::linefeed;
			}

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << r2::linefeed;
			}
		}



		lua_close( lua_state_obj );
	}
}
