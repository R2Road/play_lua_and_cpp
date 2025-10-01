#include "menu_sol2.hpp"

#include "r2tm/r2tm_director.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "play_sol2.hpp"

#include "menu_main.hpp"

r2tm::TitleFunctionT Menu_Sol2::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Sol2";
	};
}
r2tm::DescriptionFunctionT Menu_Sol2::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return (
			"> Ref : https://github.com/ThePhD/sol2"
		);
	};
}
r2tm::WriteFunctionT Menu_Sol2::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', play_sol2::Basic() );
		


		mp->AddSplit();



		mp->AddMenu( 27, Menu_Main() );
	};
}