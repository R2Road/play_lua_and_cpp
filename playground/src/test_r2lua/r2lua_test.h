#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace r2lua_test
{
	class ValueTest_1 : public r2cm::iItem, public r2cm::SingleTon<ValueTest_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class ValueTest_2 : public r2cm::iItem, public r2cm::SingleTon<ValueTest_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PushTest : public r2cm::iItem, public r2cm::SingleTon<PushTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetValueFromStackTest : public r2cm::iItem, public r2cm::SingleTon<GetValueFromStackTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetValuesFromStackTest : public r2cm::iItem, public r2cm::SingleTon<GetValuesFromStackTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class CallTest : public r2cm::iItem, public r2cm::SingleTon<CallTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
