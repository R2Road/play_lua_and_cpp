#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace stack_test
{
	class PushTest : public r2cm::iItem, public r2cm::SingleTon<PushTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class TypeCheck : public r2cm::iItem, public r2cm::SingleTon<TypeCheck>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PrintAll: public r2cm::iItem, public r2cm::SingleTon<PrintAll>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetTest_1 : public r2cm::iItem, public r2cm::SingleTon<GetTest_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetTest_2 : public r2cm::iItem, public r2cm::SingleTon<GetTest_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};


	class SetTop : public r2cm::iItem, public r2cm::SingleTon<SetTop>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Pop : public r2cm::iItem, public r2cm::SingleTon<Pop>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};



	class PushValueTest : public r2cm::iItem, public r2cm::SingleTon<PushValueTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class CopyTest : public r2cm::iItem, public r2cm::SingleTon<CopyTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class RotateTest : public r2cm::iItem, public r2cm::SingleTon<RotateTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
