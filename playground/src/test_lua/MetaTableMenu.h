#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class MetaTableMenu
{
private:
	MetaTableMenu() = delete;

public:
	static const char* GetTitle() { return "Meta Table"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};