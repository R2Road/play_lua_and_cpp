#include "MemoryAllocationMenu.h"

#include "r2tm/r2tm_director.hpp"

#include "test/memory_allocation_test.h"

#include "LuaRootMenu.h"

r2tm::TitleFunctionT MemoryAllocationMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Memory Allocation";
	};
}
r2tm::DescriptionFunctionT MemoryAllocationMenu::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT MemoryAllocationMenu::GetWriteFunction() const
{
	return[]( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', memory_allocation_test::Basic() );
		mp->AddItem( '2', memory_allocation_test::Custom() );
		mp->AddItem( '3', memory_allocation_test::Pool_1() );
		mp->AddItem( '4', memory_allocation_test::Pool_2() );



		mp->AddSplit();



		mp->AddMenu( 27, LuaRootMenu() );
	};
}