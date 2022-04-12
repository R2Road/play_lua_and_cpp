#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TestLuaRootMenu
{
private:
	TestLuaRootMenu() = delete;

public:
	static const char* GetTitle() { return "Test Lua"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};