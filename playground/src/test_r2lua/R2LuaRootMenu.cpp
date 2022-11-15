#include "R2LuaRootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "r2lua_test.h"

#include "MainMenu.h"

r2cm::MenuUp R2LuaRootMenu::Create( r2cm::Director& director )
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
		ret->AddItem( '6', r2lua_test::CallTest::GetInstance() );
		


		ret->AddSplit();



		ret->AddMenu<MainMenu>( 27 );
	}

	return ret;
}