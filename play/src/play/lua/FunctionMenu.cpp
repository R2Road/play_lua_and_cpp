#include "FunctionMenu.h"

#include "r2tm/r2tm_director.hpp"

#include "function_closure_test.h"
#include "function_cpp2lua_test.h"
#include "function_lua2cpp_test.h"

#include "LuaRootMenu.h"

r2tm::TitleFunctionT FunctionMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Function";
	};
}
r2tm::DescriptionFunctionT FunctionMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT FunctionMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', function_cpp2lua_test::Basic() );
		mp->AddItem( '2', function_cpp2lua_test::Argument() );


		mp->AddLineFeed();


		mp->AddItem( 'q', function_lua2cpp_test::Register_And_PCall() );
		mp->AddItem( 'w', function_lua2cpp_test::Argument() );
		mp->AddItem( 'e', function_lua2cpp_test::Lambda() );


		mp->AddLineFeed();


		mp->AddItem( 'a', function_closure_test::Basic() );
		mp->AddItem( 's', function_closure_test::UpdateUpvalue() );
		mp->AddItem( 'd', function_closure_test::ArgumentTest() );


		mp->AddSplit();


		mp->AddMenu( 27, LuaRootMenu() );
	};
}