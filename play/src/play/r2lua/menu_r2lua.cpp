#include "menu_r2lua.hpp"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "play_r2lua.hpp"

#include "menu_main.hpp"

r2tm::TitleFunctionT Menu_R2Lua::GetTitleFunction() const
{
	return []()->const char*
	{
		return "R2Lua";
	};
}
r2tm::DescriptionFunctionT Menu_R2Lua::GetDescriptionFunction() const
{
	return []()->const char* { return "> Add Some One"; };
}
r2tm::WriteFunctionT Menu_R2Lua::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', play_r2lua::Type_Bool() );
		mp->AddItem( '2', play_r2lua::Type_Number() );
		mp->AddItem( '3', play_r2lua::Type_String() );
		mp->AddItem( '4', play_r2lua::Value() );



		mp->AddLineFeed();



		mp->AddItem( 'q', play_r2lua::PushTest() );
		mp->AddItem( 'w', play_r2lua::GetValueFromStackTest() );
		mp->AddItem( 'e', play_r2lua::GetValuesFromStackTest() );
		mp->AddItem( 'r', play_r2lua::CallTest() );
		


		mp->AddSplit();



		mp->AddMenu( 27, Menu_Main() );
	};
}