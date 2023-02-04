#include "GlobalMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/global_test.h"

#include "LuaRootMenu.h"

r2cm::MenuUp GlobalMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', global_test::Basic_1() );
		ret->AddItem( '2', global_test::Basic_2() );


		ret->AddSplit();


		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}