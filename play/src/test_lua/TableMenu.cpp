#include "TableMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/table_test.h"

#include "LuaRootMenu.h"

r2cm::MenuUp TableMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', table_test::GenerateTest() );
		ret->AddItem( '2', table_test::Add2GlobalTest() );
		ret->AddItem( '3', table_test::PushAndGetTest_1() );
		ret->AddItem( '4', table_test::PushAndGetTest_2() );
		ret->AddItem( '5', table_test::PushAndGetTest_3() );
		ret->AddItem( '6', table_test::PushAndGetTest_4() );


		ret->AddLineFeed();


		ret->AddItem( 'q', table_test::LuaFunction_And_GetTable() );


		ret->AddLineFeed();


		ret->AddItem( 'a', table_test::GetField() );
		ret->AddItem( 's', table_test::SetField() );


		ret->AddSplit();


		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}