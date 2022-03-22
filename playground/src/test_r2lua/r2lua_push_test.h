﻿#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2/r2_Singleton.h"

namespace r2lua_push_test
{
	class PushTest : public r2cm::iItem, public r2::SingleTon<PushTest>
	{
	public:
		TitleFuncT GetTitleFunction() const override;
		DoFuncT GetDoFunction() override;
	};
}
