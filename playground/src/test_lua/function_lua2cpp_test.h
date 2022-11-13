#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace function_lua2cpp_test
{
	class Register_And_PCall : public r2cm::iItem, public r2cm::SingleTon<Register_And_PCall>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Argument : public r2cm::iItem, public r2cm::SingleTon<Argument>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}
