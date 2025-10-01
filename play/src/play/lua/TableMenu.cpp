#include "TableMenu.h"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "table_test.h"

#include "LuaRootMenu.h"

r2tm::TitleFunctionT TableMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Table";
	};
}
r2tm::DescriptionFunctionT TableMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT TableMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', table_test::GenerateTest() );
		mp->AddItem( '2', table_test::Add2GlobalTest() );
		mp->AddItem( '3', table_test::PushAndGetTest_1() );
		mp->AddItem( '4', table_test::PushAndGetTest_2() );
		mp->AddItem( '5', table_test::PushAndGetTest_3() );
		mp->AddItem( '6', table_test::PushAndGetTest_4() );


		mp->AddLineFeed();


		mp->AddItem( 'q', table_test::LuaFunction_And_GetTable() );


		mp->AddLineFeed();


		mp->AddItem( 'a', table_test::GetField() );
		mp->AddItem( 's', table_test::SetField() );


		mp->AddSplit();


		mp->AddMenu( 27, LuaRootMenu() );
	};
}