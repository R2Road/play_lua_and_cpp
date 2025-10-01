//
// # ref
// - EN Manual : https://www.lua.org/manual/5.4/manual.html
// - KR Manual : https://wariua.github.io/lua-manual/5.4/
// - ... : http://lua-users.org/wiki/MathLibraryTutorial
// - Dave Poo : Embedding Lua in C++ : https://www.youtube.com/playlist?list=PLLwK93hM93Z3nhfJyRRWGRXHaXgNX0Itk
//

//
// Vld
//
#if defined( DEBUG ) || defined( _DEBUG )
	#include "vld/include/vld.h"
#endif

//
// Lua lib
//
#if defined( _WIN64 )
	#pragma comment( lib, "external/lua/x64/liblua54.a" )
#else
	#pragma comment( lib, "external/lua/x86/liblua54.a" )
#endif

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "menu_main.hpp"

int main()
{
	//
	// Environment : Title
	//
	r2tm::WindowsUtility::ChangeTitle( "play_lua_and_cpp" );

	//
	// Environment : Size
	//
	r2tm::WindowsUtility::Resize( 1024, 960 );

	//
	// Environment : Position
	//
	r2tm::WindowsUtility::Move( 0, 0 );

	//
	// Setup
	//
	r2tm::Director director;
	director.Setup( Menu_Main() );

	//
	// Process
	//
	director.Run();

	return 0;
}

