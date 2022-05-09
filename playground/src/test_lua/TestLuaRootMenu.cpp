#include "pch.h"
#include "TestLuaRootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "lua_state_test.h"
#include "luaL_dofile_test.h"
#include "luaL_dostring_test.h"
#include "luaL_openlibs_test.h"

#include "FunctionMenu.h"
#include "GlobalMenu.h"
#include "MainMenu.h"
#include "StackMenu.h"
#include "TableMenu.h"
#include "UserDataMenu.h"

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
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( StackMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'3'
			, []()->const char* { return GlobalMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( GlobalMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem( '4', luaL_dostring_test::Basic::GetInstance() );
		ret->AddItem( '5', luaL_dofile_test::Basic::GetInstance() );
		ret->AddItem( '6', luaL_openlibs_test::Basic::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem(
			'q'
			, []()->const char* { return FunctionMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( FunctionMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'w'
			, []()->const char* { return TableMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TableMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'e'
			, []()->const char* { return UserDataMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( UserDataMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return MainMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( MainMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}