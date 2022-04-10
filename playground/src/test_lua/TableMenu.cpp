#include "pch.h"
#include "TableMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "lua_table_test.h"

#include "TestLuaRootMenu.h"

r2cm::MenuUp TableMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', lua_table_test::GenerateTest::GetInstance() );
		ret->AddItem( '2', lua_table_test::Add2GlobalTest::GetInstance() );
		ret->AddItem( '3', lua_table_test::Basic::GetInstance() );
		ret->AddItem( '4', lua_table_test::PushAndGetTest::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestLuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestLuaRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}