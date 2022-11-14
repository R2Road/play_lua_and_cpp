#include "FunctionMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/function_closure_test.h"
#include "test/function_cpp2lua_test.h"
#include "test/function_lua2cpp_test.h"

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
		ret->AddItem( '2', function_cpp2lua_test::Argument::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', function_lua2cpp_test::Register_And_PCall::GetInstance() );
		ret->AddItem( 'w', function_lua2cpp_test::Argument::GetInstance() );
		ret->AddItem( 'e', function_lua2cpp_test::Lambda::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'a', function_closure_test::Basic::GetInstance() );
		ret->AddItem( 's', function_closure_test::UpdateUpvalue::GetInstance() );
		ret->AddItem( 'd', function_closure_test::ArgumentTest::GetInstance() );


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