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

	class TypeCheck : public r2cm::iItem, public r2::SingleTon<TypeCheck>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class PrintAll: public r2cm::iItem, public r2::SingleTon<PrintAll>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetTest_1 : public r2cm::iItem, public r2::SingleTon<GetTest_1>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class GetTest_2 : public r2cm::iItem, public r2::SingleTon<GetTest_2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};


	class SetTop : public r2cm::iItem, public r2::SingleTon<SetTop>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class Pop : public r2cm::iItem, public r2::SingleTon<Pop>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};



	class PushValueTest : public r2cm::iItem, public r2::SingleTon<PushValueTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class CopyTest : public r2cm::iItem, public r2::SingleTon<CopyTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};

	class RotateTest : public r2cm::iItem, public r2::SingleTon<RotateTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
