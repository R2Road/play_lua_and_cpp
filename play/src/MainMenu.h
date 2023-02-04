#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class MainMenu
{
private:
	MainMenu() = delete;

public:
	static const char* GetTitle();
	static r2cm::MenuUp Create( r2cm::Director& director );
};