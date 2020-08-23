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

std::string MakeMenuString()
{
	std::stringstream ss;
	ss << "+ Menu" << std::endl;
	ss << "1 : step_LuaState" << std::endl;
	ss << "2 : step_DoString" << std::endl;

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

		case 27: // ESC
			return 0;
		}

		std::cout << std::endl << "Press Any Key" << std::endl;
		_getch();
		system( "cls" );
	}


	return 0;
}
