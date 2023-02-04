#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class UserDataMenu
{
private:
	UserDataMenu() = delete;

public:
	static const char* GetTitle() { return "UserData And MetaTable"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};