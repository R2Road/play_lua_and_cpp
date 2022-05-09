#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace function_lua2cpp_test
{
	class Basic_1 : public r2cm::iItem, public r2cm::SingleTon<Basic_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Basic_2 : public r2cm::iItem, public r2cm::SingleTon<Basic_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
