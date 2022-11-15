#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class UserDataMenu
{
private:
	UserDataMenu() = delete;

public:
	static const char* GetTitle() { return "UserData And MetaTable"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};