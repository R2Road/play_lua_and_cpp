#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace table_test
{
	class GenerateTest : public r2cm::iItem, public r2cm::SingleTon<GenerateTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class Add2GlobalTest : public r2cm::iItem, public r2cm::SingleTon<Add2GlobalTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class PushAndGetTest_1 : public r2cm::iItem, public r2cm::SingleTon<PushAndGetTest_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class PushAndGetTest_2 : public r2cm::iItem, public r2cm::SingleTon<PushAndGetTest_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class PushAndGetTest_3 : public r2cm::iItem, public r2cm::SingleTon<PushAndGetTest_3>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class PushAndGetTest_4 : public r2cm::iItem, public r2cm::SingleTon<PushAndGetTest_4>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class LuaFunction_And_GetTable : public r2cm::iItem, public r2cm::SingleTon<LuaFunction_And_GetTable>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}