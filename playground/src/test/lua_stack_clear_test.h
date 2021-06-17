#pragma once

#include "base/r2_iTest.h"
#include "base/r2_Singleton.h"

namespace lua_stack_clear_test
{
	class SetTop : public r2::iTest, public r2::SingleTon<SetTop>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}
