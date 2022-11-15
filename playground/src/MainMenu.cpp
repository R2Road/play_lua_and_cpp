#include "MainMenu.h"

#include <string>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "test_lua_helper.h"
#include "test_lua/LuaRootMenu.h"
#include "test_r2lua/R2LuaRootMenu.h"

const char* MainMenu::GetTitle()
{
	static const std::string ret =
		std::string( "Main Menu" )
		+ " : <" + r2cm::VersionInfo.String4Version + ">"
		+ " : <" + "lua version : v" + std::to_string( test_lua_helper::GetVersion() ) + ">";
	return ret.c_str();
}
r2cm::MenuUp MainMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, "> Add Some One"
	) );

	{
		ret->AddMenu<LuaRootMenu>( '1' );
		ret->AddMenu<R2LuaRootMenu>( '2' );



		ret->AddSplit();



		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eItemLeaveAction { return r2cm::eItemLeaveAction::Exit; }
		);
	}

	return ret;
}