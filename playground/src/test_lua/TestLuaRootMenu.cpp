#include "pch.h"
#include "TestLuaRootMenu.h"

#include <conio.h>
#include <sstream>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "lua_state_test.h"
#include "luaL_dofile_test.h"
#include "luaL_dostring_test.h"
#include "luaL_openlibs_test.h"

#include "function_cpp2lua_test.h"
#include "function_lua2cpp_test.h"

#include "GlobalMenu.h"
#include "MainMenu.h"
#include "StackMenu.h"
#include "TableMenu.h"

r2cm::MenuUp TestLuaRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', lua_state_test::Basic::GetInstance() );
		ret->AddItem(
			'2'
			, []()->const char* { return StackMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( StackMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'3'
			, []()->const char* { return GlobalMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( GlobalMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem( '4', luaL_dostring_test::Basic::GetInstance() );
		ret->AddItem( '5', luaL_dofile_test::Basic::GetInstance() );
		ret->AddItem( '6', luaL_openlibs_test::Basic::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem(
			'q'
			, []()->const char* { return TableMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TableMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);


		ret->AddLineFeed();


		ret->AddItem( 'a', function_cpp2lua_test::Basic::GetInstance() );
		ret->AddItem( 's', function_cpp2lua_test::Argument2::GetInstance() );
		ret->AddItem( 'd', function_cpp2lua_test::GetTable::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'z', function_lua2cpp_test::Basic::GetInstance() );
		


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return MainMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( MainMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}