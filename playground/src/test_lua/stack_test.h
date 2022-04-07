#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace stack_test
{
	class PushTest : public r2cm::iItem, public r2::SingleTon<PushTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetTest : public r2cm::iItem, public r2::SingleTon<GetTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class StackPrinterTest : public r2cm::iItem, public r2::SingleTon<StackPrinterTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
