#include "LuaRootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/lua_state_test.h"
#include "test/luaL_dofile_test.h"
#include "test/luaL_dostring_test.h"
#include "test/luaL_openlibs_test.h"

#include "FunctionMenu.h"
#include "GlobalMenu.h"
#include "MainMenu.h"
#include "StackMenu.h"
#include "TableMenu.h"
#include "UserData_And_MetaTable_Menu.h"

r2cm::MenuUp LuaRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', lua_state_test::Basic::GetInstance() );
		ret->AddMenu<StackMenu>( '2' );
		ret->AddMenu<GlobalMenu>( '3' );
		ret->AddItem( '4', luaL_dostring_test::Basic::GetInstance() );
		ret->AddItem( '5', luaL_dofile_test::Basic::GetInstance() );
		ret->AddItem( '6', luaL_openlibs_test::Basic::GetInstance() );



		ret->AddLineFeed();



		ret->AddMenu<FunctionMenu>( 'q' );
		ret->AddMenu<TableMenu>( 'w' );



		ret->AddLineFeed();



		ret->AddMenu<UserDataMenu>( 's' );



		ret->AddSplit();



		ret->AddMenu<MainMenu>( 27 );
	}

	return ret;
}