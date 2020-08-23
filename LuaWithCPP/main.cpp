#include "pch.h"

#include <conio.h>
#include <iostream>
#include <sstream>
#include <utility>
#include <Windows.h>

#ifdef _WIN32
#pragma comment( lib, "lua54/liblua54.a" )
#endif

#include "step_LuaState.h"
#include "step_DoString.h"
#include "step_GetGlobal.h"
#include "step_IsNumber.h"
#include "step_OpenLibs.h"
#include "step_DoFile.h"

std::string MakeMenuString()
{
	std::stringstream ss;
	ss << "+ Menu" << std::endl;
	ss << "1 : step_LuaState" << std::endl;
	ss << "2 : step_DoString" << std::endl;
	ss << "3 : step_GetGlobal" << std::endl;
	ss << "4 : step_IsNumber" << std::endl;
	ss << "5 : step_OpenLibs" << std::endl;
	ss << "6 : step_DoFile" << std::endl;

	ss << std::endl << "Press Number" << std::endl;

	return std::string( ss.str() );
}

void ShowMenu()
{
	static std::string menu_string( std::move( MakeMenuString() ) );
	std::cout << menu_string;
}

int main()
{
	int input = 0;
	while( true )
	{
		ShowMenu();

		input = _getch();
		system( "cls" );

		switch( input )
		{
		case '1':
			step_LuaState();
			break;
		case '2':
			step_DoString();
			break;
		case '3':
			step_GetGlobal();
			break;
		case '4':
			step_IsNumber();
			break;
		case '5':
			step_OpenLibs();
			break;
		case '6':
			step_DoFile();
			break;

		case 27: // ESC
			return 0;
		}

		std::cout << std::endl << "Press Any Key" << std::endl;
		_getch();
		system( "cls" );
	}


	return 0;
}
