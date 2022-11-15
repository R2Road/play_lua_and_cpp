#include "UserData_And_MetaTable_Menu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/metatable_test.h"
#include "test/userdata_test.h"

#include "LuaRootMenu.h"

r2cm::MenuUp UserDataMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', userdata_test::New::GetInstance() );
		ret->AddItem( '2', userdata_test::Constructor::GetInstance() );
		ret->AddItem( '3', metatable_test::Basic::GetInstance() );
		ret->AddItem( '4', userdata_test::Destructor::GetInstance() );



		ret->AddLineFeed();



		ret->AddItem( 'q', userdata_test::OOP::GetInstance() );
		ret->AddItem( 'w', userdata_test::OOP_2::GetInstance() );
		ret->AddItem( 'e', userdata_test::Field::GetInstance() );
		ret->AddItem( 'r', userdata_test::Field_2::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}