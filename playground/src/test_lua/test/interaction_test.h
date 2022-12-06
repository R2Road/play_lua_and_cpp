#pragma once

#include "r2cm/r2cm_iItem.h"

namespace interaction_test
{
	class CallWithClosure : public r2cm::iItem
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() const override;
	};
}
