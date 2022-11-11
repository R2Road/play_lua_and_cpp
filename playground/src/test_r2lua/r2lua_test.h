#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace r2lua_test
{
	class ValueTest_1 : public r2cm::iItem, public r2cm::SingleTon<ValueTest_1>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class ValueTest_2 : public r2cm::iItem, public r2cm::SingleTon<ValueTest_2>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class PushTest : public r2cm::iItem, public r2cm::SingleTon<PushTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class GetValueFromStackTest : public r2cm::iItem, public r2cm::SingleTon<GetValueFromStackTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class GetValuesFromStackTest : public r2cm::iItem, public r2cm::SingleTon<GetValuesFromStackTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};

	class CallTest : public r2cm::iItem, public r2cm::SingleTon<CallTest>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}
