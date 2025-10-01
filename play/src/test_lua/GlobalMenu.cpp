#include "GlobalMenu.h"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test/global_test.h"

#include "LuaRootMenu.h"

r2tm::TitleFunctionT GlobalMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Global";
	};
}
r2tm::DescriptionFunctionT GlobalMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT GlobalMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', global_test::Basic_1() );
		mp->AddItem( '2', global_test::Basic_2() );


		mp->AddSplit();


		mp->AddMenu( 27, LuaRootMenu() );
	};
}