#include "pch.h"
#include "r2lua_Value.h"

namespace r2lua
{
	Type GetType( const Value& v )
	{
		return std::visit(
			[]( const auto& x )
			{
				return x.GetType();
			}
			, v
		);
	}
}