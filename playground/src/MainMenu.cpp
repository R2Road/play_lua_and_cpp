#include "pch.h"
#include "MainMenu.h"

#include <string>

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "test_lua_helper.h"
#include "test_lua/TestLuaRootMenu.h"
#include "test_r2lua/TestR2LuaRootMenu.h"

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
		ret->AddItem(
			'1'
			, []()->const char* { return TestLuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestLuaRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'2'
			, []()->const char* { return TestR2LuaRootMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestR2LuaRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eItemLeaveAction { return r2cm::eItemLeaveAction::Exit; }
		);
	}

	return ret;
}