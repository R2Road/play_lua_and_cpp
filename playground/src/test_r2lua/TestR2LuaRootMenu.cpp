#include "pch.h"
#include "TestR2LuaRootMenu.h"

#include <conio.h>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "MainMenu.h"

#include "r2lua_test.h"

r2cm::MenuUp TestR2LuaRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', r2lua_test::ValueTest_1::GetInstance() );
		ret->AddItem( '2', r2lua_test::ValueTest_2::GetInstance() );
		ret->AddItem( '3', r2lua_test::PushTest::GetInstance() );
		ret->AddItem( '4', r2lua_test::GetValueFromStackTest::GetInstance() );
		ret->AddItem( '5', r2lua_test::GetValuesFromStackTest::GetInstance() );
		

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