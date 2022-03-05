#pragma once

#include "base/r2_iTest.h"
#include "r2/r2_Singleton.h"

namespace lua_stack_clear_test
{
	class SetTop : public r2::iItem, public r2::SingleTon<SetTop>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class Pop : public r2::iItem, public r2::SingleTon<Pop>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}
