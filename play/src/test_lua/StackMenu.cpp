#include "StackMenu.h"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test/stack_test.h"

#include "LuaRootMenu.h"

r2tm::TitleFunctionT StackMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Lua";
	};
}
r2tm::DescriptionFunctionT StackMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT StackMenu::GetWriteFunction() const
{
	return[]( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', stack_test::PushTest() );
		mp->AddItem( '2', stack_test::TypeCheck() );
		mp->AddItem( '3', stack_test::TypeName() );
		mp->AddItem( '4', stack_test::PrintAll() );
		mp->AddItem( '5', stack_test::GetTest_1() );
		mp->AddItem( '6', stack_test::GetTest_2() );
		mp->AddItem( '7', stack_test::SetTop() );
		mp->AddItem( '8', stack_test::Pop() );

		mp->AddLineFeed();

		mp->AddItem( 'q', stack_test::PushValueTest() );
		mp->AddItem( 'w', stack_test::CopyTest() );
		mp->AddItem( 'e', stack_test::RotateTest() );


		mp->AddSplit();


		mp->AddMenu( 27, LuaRootMenu() );
	};
}