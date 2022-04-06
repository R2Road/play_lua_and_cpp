#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace lua_table_test
{
	class GenerateTest : public r2cm::iItem, public r2::SingleTon<GenerateTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Basic : public r2cm::iItem, public r2::SingleTon<Basic>
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
}