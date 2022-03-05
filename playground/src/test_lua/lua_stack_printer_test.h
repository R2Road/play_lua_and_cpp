﻿#pragma once

#include "base/r2_iTest.h"
#include "r2/r2_Singleton.h"

namespace lua_stack_printer_test
{
	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}
