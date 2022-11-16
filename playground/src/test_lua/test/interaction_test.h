#pragma once

#include "r2cm/r2cm_iItem.h"
#include "r2cm/r2cm_Singleton.h"

namespace interaction_test
{
	class CallWithClosure : public r2cm::iItem, public r2cm::SingleTon<CallWithClosure>
	{
	public:
		TitleFunctionT GetTitleFunction() const override;
		DoFunctionT GetDoFunction() override;
	};
}
