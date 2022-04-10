#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TableMenu
{
private:
	TableMenu() = delete;

public:
	static const char* GetTitle() { return "Table"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};