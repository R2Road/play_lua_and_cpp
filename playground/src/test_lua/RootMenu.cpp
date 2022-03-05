#include "pch.h"
#include "RootMenu.h"

#include <conio.h>
#include <sstream>

#include "base/r2cm_Director.h"
#include "base/r2_eTestResult.h"

#include "lua_state_test.h"
#include "lua_dostring_test.h"
#include "lua_getglobal_test.h"
#include "lua_type_check_test.h"
#include "lua_stack_printer_test.h"
#include "lua_stack_clear_test.h"

#include "lua_open_libs_test.h"
#include "step_DoFile.h"
#include "step_GetTable.h"
#include "step_PCall_01.h"
#include "step_PCall_02.h"
#include "step_PCall_03.h"
#include "step_PCall_04_CallCPPFunction.h"

namespace
{
	std::string MakeMenuString()
	{
		std::stringstream ss;
		ss << "+ Menu" << r2::linefeed;
		ss << "6 : step_DoFile" << r2::linefeed;
		ss << "7 : step_GetTable" << r2::linefeed;

		ss << r2::linefeed;

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

namespace r2
{
	r2cm::MenuUp RootMenu::Create( r2cm::Director& director )
	{
		r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
			director
			, GetTitle()
			, "> Add Some One"
		) );

		{
			ret->AddItem( '1', lua_state_test::Basic::GetInstance() );
			ret->AddItem( '2', lua_dostring_test::Basic::GetInstance() );
			ret->AddItem( '3', lua_getglobal_test::Basic::GetInstance() );
			ret->AddItem( '4', lua_type_check_test::Basic::GetInstance() );
			ret->AddItem( '5', lua_stack_printer_test::Basic::GetInstance() );


			ret->AddLineFeed();


			ret->AddItem( '6', lua_stack_clear_test::SetTop::GetInstance() );
			ret->AddItem( '7', lua_stack_clear_test::Pop::GetInstance() );


			ret->AddLineFeed();


			ret->AddItem( 'q', lua_open_libs_test::Basic::GetInstance() );


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
						case '6':
							step::DoFile();
							break;
						case '7':
							step::GetTable();
							break;

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

					return r2cm::eTestEndAction::None;
				}
			);


			ret->AddSplit();


			ret->AddItem(
				27
				, []()->const char* { return "Exit"; }
				, []()->r2cm::eTestEndAction { return r2cm::eTestEndAction::Exit; }
			);
		}

		return ret;
	}
}