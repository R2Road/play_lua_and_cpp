#ifndef PCH_H
#define PCH_H

#include <iostream>

//
// Lua
//
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#if defined( _WIN64 )
	#pragma comment( lib, "lua/x64/liblua54.a" )
#else
	#pragma comment( lib, "lua/x86/liblua54.a" )
#endif

#include "test_lua_helper.h"

#endif //PCH_H
