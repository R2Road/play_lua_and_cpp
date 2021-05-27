#include "pch.h"

#include "step_helper.h"
#include "step_DoFile.h"

namespace step
{
	void DoFile()
	{
		lua_State* lua_state_obj = luaL_newstate();



		std::cout << "Call : luaL_openlibs" << std::endl;
		luaL_openlibs( lua_state_obj );

		std::cout << std::endl;

		//
		// Test x 0
		//
		{
			std::cout << "# Test 0" << std::endl;

			const int result = luaL_dofile( lua_state_obj, "Resources/step_DoFile_00.lua" );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "DoFile Failed" << std::endl;
				std::cout << error_message << std::endl;
			}
			else
			{
				std::cout << "DoFile Success" << std::endl;
			}

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << std::endl;
			}
		}

		std::cout << std::endl;

		//
		// Test x 1
		//
		{
			std::cout << "# Test 1" << std::endl;

			const int result = luaL_dofile( lua_state_obj, "Resources/step_DoFile_01.lua" );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "DoFile Failed" << std::endl;
				std::cout << error_message << std::endl;
			}
			else
			{
				std::cout << "DoFile Success" << std::endl;
			}

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << std::endl;
			}
		}

		std::cout << std::endl;

		//
		// Test x 2
		//
		{
			std::cout << "# Test 2" << std::endl;

			const int result = luaL_dofile( lua_state_obj, "Resources/step_DoFile_02.lua" );
			if( result != LUA_OK )
			{
				const auto error_message = lua_tostring( lua_state_obj, -1 );

				std::cout << "DoFile Failed" << std::endl;
				std::cout << error_message << std::endl;
			}
			else
			{
				std::cout << "DoFile Success" << std::endl;
			}

			lua_getglobal( lua_state_obj, "a" );

			if( lua_isnumber( lua_state_obj, -1 ) )
			{
				const auto a = static_cast<float>( lua_tonumber( lua_state_obj, -1 ) );
				std::cout << "result : " << "a : " << a << std::endl;
			}
		}



		lua_close( lua_state_obj );
	}
}
