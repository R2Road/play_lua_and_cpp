#include "pch.h"
#include "r2_RootMenu.h"

#include <conio.h>
#include <sstream>

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"

#include "step/step_LuaState.h"
#include "step/step_DoString.h"
#include "step/step_GetGlobal.h"
#include "step/step_IsNumber.h"
#include "step/step_OpenLibs.h"
#include "step/step_DoFile.h"
#include "step/step_GetTable.h"
#include "step/step_PCall_01.h"
#include "step/step_PCall_02.h"
#include "step/step_PCall_03.h"
#include "step/step_PCall_04_CallCPPFunction.h"

namespace
{
	std::string MakeMenuString()
	{
		std::stringstream ss;
		ss << "+ Menu" << r2::linefeed;
		ss << "1 : step_LuaState" << r2::linefeed;
		ss << "2 : step_DoString" << r2::linefeed;
		ss << "3 : step_GetGlobal" << r2::linefeed;
		ss << "4 : step_IsNumber" << r2::linefeed;
		ss << "5 : step_OpenLibs" << r2::linefeed;
		ss << "6 : step_DoFile" << r2::linefeed;
		ss << "7 : step_GetTable" << r2::linefeed;

		ss << r2::linefeed;

		ss << "Q : step_PCall_01" << r2::linefeed;
		ss << "W : step_PCall_02" << r2::linefeed;
		ss << "E : step_PCall_03" << r2::linefeed;
		ss << "R : step_PCall_04_CallCPPFunction" << r2::linefeed;

		ss << std::endl << "Press Number" << r2::linefeed;

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
			ret->AddChild(
				'1'
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
						case '1':
							step::LuaState();
							break;
						case '2':
							step::DoString();
							break;
						case '3':
							step::GetGlobal();
							break;
						case '4':
							step::IsNumber();
							break;
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

						std::cout << std::endl << "Press Any Key" << r2::linefeed;
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