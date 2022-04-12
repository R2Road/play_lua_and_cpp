#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace table_test
{
	class GenerateTest : public r2cm::iItem, public r2::SingleTon<GenerateTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Add2GlobalTest : public r2cm::iItem, public r2::SingleTon<Add2GlobalTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PushAndGetTest : public r2cm::iItem, public r2::SingleTon<PushAndGetTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PushAndGetTest_2 : public r2cm::iItem, public r2::SingleTon<PushAndGetTest_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}