#include "FunctionMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/function_closure_test.h"
#include "test/function_cpp2lua_test.h"
#include "test/function_lua2cpp_test.h"

#include "LuaRootMenu.h"

r2cm::MenuUp FunctionMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', function_cpp2lua_test::Basic() );
		ret->AddItem( '2', function_cpp2lua_test::Argument() );


		ret->AddLineFeed();


		ret->AddItem( 'q', function_lua2cpp_test::Register_And_PCall() );
		ret->AddItem( 'w', function_lua2cpp_test::Argument() );
		ret->AddItem( 'e', function_lua2cpp_test::Lambda() );


		ret->AddLineFeed();


		ret->AddItem( 'a', function_closure_test::Basic() );
		ret->AddItem( 's', function_closure_test::UpdateUpvalue() );
		ret->AddItem( 'd', function_closure_test::ArgumentTest() );


		ret->AddSplit();


		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}