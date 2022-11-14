#include "lua_header_package.h"
#include "r2cm/r2cm_Inspector.h"
#include "test_lua_helper.h"

struct Data
{
	Data() : t( 777 ) {}
	int t;
};

auto cpp_process = []( lua_State* l )->int
{
	void* d = lua_newuserdata( l, sizeof( Data ) );
	new ( d ) Data;
	return 1;
};