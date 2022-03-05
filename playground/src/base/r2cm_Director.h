#pragma once

#include "r2_Menu.h"

namespace r2cm
{
	class Director
	{
	public:
		Director();

		void Setup( MenuUp menu );

		void Run();

	private:
		MenuUp mMenu;
	};
}