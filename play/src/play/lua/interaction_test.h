#pragma once

#include "r2tm/r2tm_interface_item.hpp"

namespace interaction_test
{
	class CallWithClosure : public r2tm::iItem
	{
	public:
		r2tm::TitleFunctionT GetTitleFunction() const override;
		r2tm::DoFunctionT GetDoFunction() const override;
	};
}
