#pragma once

#include "r2tm/r2tm_interface_menu.hpp"

class UserDataMenu : public r2tm::iMenu
{
public:
	r2tm::TitleFunctionT GetTitleFunction() const;
	r2tm::DescriptionFunctionT GetDescriptionFunction() const;
	r2tm::WriteFunctionT GetWriteFunction() const;
};