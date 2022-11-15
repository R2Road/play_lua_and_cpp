#include "StackMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/stack_test.h"

#include "LuaRootMenu.h"

r2cm::MenuUp StackMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', stack_test::PushTest::GetInstance() );
		ret->AddItem( '2', stack_test::TypeCheck::GetInstance() );
		ret->AddItem( '3', stack_test::TypeName::GetInstance() );
		ret->AddItem( '4', stack_test::PrintAll::GetInstance() );
		ret->AddItem( '5', stack_test::GetTest_1::GetInstance() );
		ret->AddItem( '6', stack_test::GetTest_2::GetInstance() );
		ret->AddItem( '7', stack_test::SetTop::GetInstance() );
		ret->AddItem( '8', stack_test::Pop::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'q', stack_test::PushValueTest::GetInstance() );
		ret->AddItem( 'w', stack_test::CopyTest::GetInstance() );
		ret->AddItem( 'e', stack_test::RotateTest::GetInstance() );


		ret->AddSplit();


		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}