#include "pch.h"
#include "MainMenu.h"


#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test_lua/TestLuaRootMenu.h"
#include "test_r2lua/TestR2LuaRootMenu.h"

r2cm::MenuUp MainMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem(
			'1'
			, []()->const char* { return TestLuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestLuaRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'2'
			, []()->const char* { return TestR2LuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestR2LuaRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eTestEndAction { return r2cm::eTestEndAction::Exit; }
		);
	}

	return ret;
}