#include "UserData_And_MetaTable_Menu.h"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test/interaction_test.h"
#include "test/metatable_test.h"
#include "test/userdata_test.h"

#include "LuaRootMenu.h"

r2tm::TitleFunctionT UserDataMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "UserData And MetaTable";
	};
}
r2tm::DescriptionFunctionT UserDataMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT UserDataMenu::GetWriteFunction() const
{
	return[]( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', metatable_test::Basic() );



		mp->AddLineFeed();



		mp->AddItem( 'q', userdata_test::New() );
		mp->AddItem( 'w', userdata_test::Constructor() );
		mp->AddItem( 'e', userdata_test::Destructor() );



		mp->AddLineFeed();



		mp->AddItem( 'a', userdata_test::OOP_1() );
		mp->AddItem( 's', userdata_test::OOP_2() );
		mp->AddItem( 'd', userdata_test::Field_Get() );
		mp->AddItem( 'f', userdata_test::Field_Set() );
		mp->AddItem( 'g', userdata_test::Index_And_NewIndex() );
		mp->AddItem( 'h', userdata_test::Field_AddFromLua() );
		mp->AddItem( 'j', interaction_test::CallWithClosure() );



		mp->AddSplit();



		mp->AddMenu( 27, LuaRootMenu() );
	};
}