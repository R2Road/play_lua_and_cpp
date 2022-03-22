#pragma once

#include <string>
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
		Number( lua_Number num ) : mType( Type::Number ), mValue( num ) {}

		Type GetType() const { return mType; }

	private:
		Type mType;
		lua_Number mValue;
	};
	class String
	{
	public:
		String( const char* const str ) : mType( Type::String ), mValue( str ) {}

		Type GetType() const { return mType; }

	private:
		Type mType;
		std::string mValue;
	};



	using Value = std::variant<Number, String>;



	Type GetType( const Value& v );
}
