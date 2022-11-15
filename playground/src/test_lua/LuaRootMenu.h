#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class LuaRootMenu
{
private:
	LuaRootMenu() = delete;

public:
	static const char* GetTitle() { return "Lua"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};