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

#include "test_lua_helper.h"

#endif //PCH_H
