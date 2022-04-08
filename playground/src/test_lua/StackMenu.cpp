#include "pch.h"
#include "StackMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "stack_test.h"

#include "TestLuaRootMenu.h"

r2cm::MenuUp StackMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', stack_test::PushTest::GetInstance() );
		ret->AddItem( '2', stack_test::GetTest::GetInstance() );
		ret->AddItem( '3', stack_test::PrintAllTest::GetInstance() );
		ret->AddItem( '4', stack_test::SetTop::GetInstance() );
		ret->AddItem( '5', stack_test::Pop::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'q', stack_test::CopyTest::GetInstance() );


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