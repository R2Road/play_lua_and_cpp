#include "LuaRootMenu.h"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test/lua_state_test.h"
#include "test/luaL_dofile_test.h"
#include "test/luaL_dostring_test.h"
#include "test/luaL_openlibs_test.h"

#include "FunctionMenu.h"
#include "GlobalMenu.h"
#include "MainMenu.h"
#include "MemoryAllocationMenu.h"
#include "StackMenu.h"
#include "TableMenu.h"
#include "UserData_And_MetaTable_Menu.h"

r2tm::TitleFunctionT LuaRootMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Lua";
	};
}
r2tm::DescriptionFunctionT LuaRootMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT LuaRootMenu::GetWriteFunction() const
{
	return[]( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', lua_state_test::Basic() );
		mp->AddMenu( '2', StackMenu() );
		mp->AddMenu( '3', GlobalMenu() );
		mp->AddItem( '4', luaL_dostring_test::Basic() );
		mp->AddItem( '5', luaL_dofile_test::Basic() );
		mp->AddItem( '6', luaL_openlibs_test::Basic() );



		mp->AddLineFeed();



		mp->AddMenu( 'q', FunctionMenu() );
		mp->AddMenu( 'w', TableMenu() );
		mp->AddMenu( 'e', MemoryAllocationMenu() );



		mp->AddLineFeed();



		mp->AddMenu( 'a', UserDataMenu() );



		mp->AddSplit();



		mp->AddMenu( 27, MainMenu() );
	};
}