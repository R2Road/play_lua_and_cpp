#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class MemoryAllocationMenu
{
private:
	MemoryAllocationMenu() = delete;

public:
	static const char* GetTitle() { return "Memory Allocation"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};