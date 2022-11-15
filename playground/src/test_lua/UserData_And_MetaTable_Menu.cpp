#include "UserData_And_MetaTable_Menu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/metatable_test.h"
#include "test/userdata_test.h"

#include "TestLuaRootMenu.h"

r2cm::MenuUp UserDataMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', userdata_test::New::GetInstance() );
		ret->AddItem( '2', metatable_test::Basic::GetInstance() );
		ret->AddItem( '3', userdata_test::Constructor::GetInstance() );
		ret->AddItem( '4', userdata_test::Destructor::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestLuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestLuaRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}