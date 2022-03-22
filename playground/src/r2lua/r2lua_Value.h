#pragma once

#include <variant>

//
// # REF
// CppCon 2017: Andreas Weis “Howling at the Moon: Lua for C++ Programmers”
// https://www.youtube.com/watch?v=pfwHCiP1HFM
//

namespace r2lua
{
	enum class Type
	{
		Number,
		String,
	};



	class Number
	{
	public:
		Type GetType() const { return mType; }

	private:
		Type mType;
	};
	class String
	{
	public:
		Type GetType() const { return mType; }

	private:
		Type mType;
	};



	using Value = std::variant<Number, String>;



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
