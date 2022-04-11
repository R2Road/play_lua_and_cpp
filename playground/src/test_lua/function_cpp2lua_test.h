#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace function_cpp2lua_test
{
	class Argument2 : public r2cm::iItem, public r2::SingleTon<Argument2>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
