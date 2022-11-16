#include "MemoryAllocationMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/memory_allocation_test.h"

#include "LuaRootMenu.h"

r2cm::MenuUp MemoryAllocationMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', memory_allocation_test::Basic::GetInstance() );
		ret->AddItem( '2', memory_allocation_test::Custom::GetInstance() );
		ret->AddItem( '3', memory_allocation_test::Pool_1::GetInstance() );
		ret->AddItem( '4', memory_allocation_test::Pool_2::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<LuaRootMenu>( 27 );
	}

	return ret;
}