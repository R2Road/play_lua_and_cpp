#include "menu_main.hpp"

#include <string>

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_version_info.hpp"

#include "test_lua_helper.h"
#include "play/lua/LuaRootMenu.h"
#include "play/r2lua/menu_r2lua.hpp"
#include "play/sol2/menu_sol2.hpp"

r2tm::TitleFunctionT Menu_Main::GetTitleFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
			std::string( "Main Menu" )
			+ " : <" + r2tm::VersionInfo.String4Version + ">"
			+ " : <" + "lua version : v" + std::to_string( test_lua_helper::GetVersion() ) + ">";
		return ret.c_str();
	};
}
r2tm::DescriptionFunctionT Menu_Main::GetDescriptionFunction() const
{
	return []()->const char* { return ""; };
}
r2tm::WriteFunctionT Menu_Main::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMenu( '1', LuaRootMenu() );
		mp->AddMenu( '2', Menu_R2Lua() );



		mp->AddLineFeed();



		mp->AddMenu( 'q', Menu_Sol2() );



		mp->AddSplit();



		mp->AddExit( 27 );
	};
}