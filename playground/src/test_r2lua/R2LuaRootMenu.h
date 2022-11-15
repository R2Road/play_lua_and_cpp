#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class R2LuaRootMenu
{
private:
	R2LuaRootMenu() = delete;

public:
	static const char* GetTitle() { return "R2Lua"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};