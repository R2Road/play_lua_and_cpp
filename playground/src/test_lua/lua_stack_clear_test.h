#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace lua_stack_clear_test
{
	class SetTop : public r2cm::iItem, public r2::SingleTon<SetTop>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Pop : public r2cm::iItem, public r2::SingleTon<Pop>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
