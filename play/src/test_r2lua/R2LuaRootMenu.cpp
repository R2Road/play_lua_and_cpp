#include "R2LuaRootMenu.h"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "r2lua_test.h"

#include "MainMenu.h"

r2tm::TitleFunctionT R2LuaRootMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "R2Lua";
	};
}
r2tm::DescriptionFunctionT R2LuaRootMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT R2LuaRootMenu::GetWriteFunction() const
{
	return[]( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', r2lua_test::ValueTest_1() );
		mp->AddItem( '2', r2lua_test::ValueTest_2() );
		mp->AddItem( '3', r2lua_test::PushTest() );
		mp->AddItem( '4', r2lua_test::GetValueFromStackTest() );
		mp->AddItem( '5', r2lua_test::GetValuesFromStackTest() );
		mp->AddItem( '6', r2lua_test::CallTest() );
		


		mp->AddSplit();



		mp->AddMenu( 27, MainMenu() );
	};
}