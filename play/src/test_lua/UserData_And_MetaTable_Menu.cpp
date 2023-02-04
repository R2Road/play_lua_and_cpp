#include "UserData_And_MetaTable_Menu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/interaction_test.h"
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
		ret->AddItem( '1', metatable_test::Basic() );



		ret->AddLineFeed();



		ret->AddItem( 'q', userdata_test::New() );
		ret->AddItem( 'w', userdata_test::Constructor() );
		ret->AddItem( 'e', userdata_test::Destructor() );



		ret->AddLineFeed();



		ret->AddItem( 'a', userdata_test::OOP_1() );
		ret->AddItem( 's', userdata_test::OOP_2() );
		ret->AddItem( 'd', userdata_test::Field_Get() );
		ret->AddItem( 'f', userdata_test::Field_Set() );
		ret->AddItem( 'g', userdata_test::Index_And_NewIndex() );
		ret->AddItem( 'h', userdata_test::Field_AddFromLua() );
		ret->AddItem( 'j', interaction_test::CallWithClosure() );



		ret->AddSplit();



		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}