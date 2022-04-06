#include "pch.h"
#include "TestLuaRootMenu.h"

#include <conio.h>
#include <sstream>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "lua_state_test.h"
#include "luaL_dostring_test.h"
#include "lua_getglobal_test.h"
#include "lua_type_check_test.h"
#include "lua_stack_printer_test.h"
#include "lua_stack_clear_test.h"

#include "luaL_openlibs_test.h"
#include "luaL_dofile_test.h"
#include "lua_table_test.h"

#include "step_PCall_01.h"
#include "step_PCall_02.h"
#include "step_PCall_03.h"
#include "step_PCall_04_CallCPPFunction.h"

#include "MainMenu.h"

namespace
{
	std::string MakeMenuString()
	{
		std::stringstream ss;
		ss << "+ Menu" << r2::linefeed;
		ss << "Q : step_PCall_01" << r2::linefeed;
		ss << "W : step_PCall_02" << r2::linefeed;
		ss << "E : step_PCall_03" << r2::linefeed;
		ss << "R : step_PCall_04_CallCPPFunction" << r2::linefeed;

		ss << r2::linefeed << "Press Number" << r2::linefeed;

		return std::string( ss.str() );
	}

	void ShowMenu()
	{
		static std::string menu_string( std::move( MakeMenuString() ) );
		std::cout << menu_string;
	}
}

r2cm::MenuUp TestLuaRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddItem( '1', lua_state_test::Basic::GetInstance() );
		ret->AddItem( '2', luaL_dostring_test::Basic::GetInstance() );
		ret->AddItem( '3', lua_getglobal_test::Basic::GetInstance() );
		ret->AddItem( '4', lua_type_check_test::Basic::GetInstance() );
		ret->AddItem( '5', lua_stack_printer_test::Basic::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( '6', lua_stack_clear_test::SetTop::GetInstance() );
		ret->AddItem( '7', lua_stack_clear_test::Pop::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', luaL_openlibs_test::Basic::GetInstance() );
		ret->AddItem( 'w', luaL_dofile_test::Basic::GetInstance() );

		ret->AddItem( 'e', lua_table_test::GenerateTest::GetInstance() );
		ret->AddItem( 'r', lua_table_test::Add2GlobalTest::GetInstance() );
		ret->AddItem( 't', lua_table_test::Basic::GetInstance() );
		ret->AddItem( 'y', lua_table_test::PushAndGetTest::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			32
			, []()->const char* { return "All"; }
			, []()->r2cm::eTestEndAction
			{
				int input = 0;
				bool process = true;
				while( process )
				{
					ShowMenu();

					input = _getch();
					system( "cls" );

					switch( input )
					{
					case 'q':
						step::PCall_01();
						break;
					case 'w':
						step::PCall_02();
						break;
					case 'e':
						step::PCall_03();
						break;
					case 'r':
						step::PCall_04_CallCPPFunction();
						break;

					case 27: // ESC
						process = false;
						break;
					}

					std::cout << r2::linefeed << "Press Any Key" << r2::linefeed;
					_getch();
					system( "cls" );
				}

				return r2cm::eTestEndAction::Pause;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return MainMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( MainMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}