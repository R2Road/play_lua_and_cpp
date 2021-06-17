#include "pch.h"
#include "r2_RootMenu.h"

#include <conio.h>
#include <sstream>

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"

#include "test/lua_state_test.h"
#include "test/lua_dostring_test.h"
#include "test/lua_getglobal_test.h"
#include "test/lua_stack_printer_test.h"
#include "test/lua_stack_clear_test.h"
#include "test/step_IsNumber.h"

#include "test/step_OpenLibs.h"
#include "test/step_DoFile.h"
#include "test/step_GetTable.h"
#include "test/step_PCall_01.h"
#include "test/step_PCall_02.h"
#include "test/step_PCall_03.h"
#include "test/step_PCall_04_CallCPPFunction.h"

namespace
{
	std::string MakeMenuString()
	{
		std::stringstream ss;
		ss << "+ Menu" << r2::linefeed;
		ss << "5 : step_OpenLibs" << r2::linefeed;
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
	MenuUp RootMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle()
			, "> Add Some One"
		) );

		{
			ret->AddChild( '1', lua_state_test::Basic::GetInstance() );
			ret->AddChild( '2', lua_dostring_test::Basic::GetInstance() );
			ret->AddChild( '3', lua_getglobal_test::Basic::GetInstance() );
			ret->AddChild( '4', lua_stack_printer_test::Basic::GetInstance() );
			ret->AddChild( '5', lua_stack_clear_test::SetTop::GetInstance() );

			ret->AddChild( '6', lua_isnumber_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				32
				, []()->const char* { return "All"; }
				, []()->eTestResult
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
						case '5':
							step::OpenLibs();
							break;
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

					return eTestResult::RunTest;
				}
			);


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Exit"; }
				, []()->eTestResult { return eTestResult::Exit; }
			);
		}

		return ret;
	}
}