#include "pch.h"
#include "FunctionMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "function_cpp2lua_test.h"
#include "function_lua2cpp_test.h"
#include "TestLuaRootMenu.h"

r2cm::MenuUp FunctionMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', function_cpp2lua_test::Basic::GetInstance() );
		ret->AddItem( '2', function_cpp2lua_test::Argument2::GetInstance() );
		ret->AddItem( '3', function_cpp2lua_test::GetTable::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', function_lua2cpp_test::Basic::GetInstance() );


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