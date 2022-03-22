#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TestR2LuaRootMenu
{
private:
	TestR2LuaRootMenu() = delete;

public:
	static const char* GetTitle() { return "Test R2Lua Root"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};