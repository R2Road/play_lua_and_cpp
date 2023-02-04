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
		ret->AddItem( '1', stack_test::PushTest() );
		ret->AddItem( '2', stack_test::TypeCheck() );
		ret->AddItem( '3', stack_test::TypeName() );
		ret->AddItem( '4', stack_test::PrintAll() );
		ret->AddItem( '5', stack_test::GetTest_1() );
		ret->AddItem( '6', stack_test::GetTest_2() );
		ret->AddItem( '7', stack_test::SetTop() );
		ret->AddItem( '8', stack_test::Pop() );

		ret->AddLineFeed();

		ret->AddItem( 'q', stack_test::PushValueTest() );
		ret->AddItem( 'w', stack_test::CopyTest() );
		ret->AddItem( 'e', stack_test::RotateTest() );


		ret->AddSplit();


		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}