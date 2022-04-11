#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace r2lua_test
{
	class ValueTest_1 : public r2cm::iItem, public r2::SingleTon<ValueTest_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class ValueTest : public r2cm::iItem, public r2::SingleTon<ValueTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PushTest : public r2cm::iItem, public r2::SingleTon<PushTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetValueFromStackTest : public r2cm::iItem, public r2::SingleTon<GetValueFromStackTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetValuesFromStackTest : public r2cm::iItem, public r2::SingleTon<GetValuesFromStackTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
