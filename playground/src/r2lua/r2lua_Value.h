#pragma once

#include <string>
#include <string_view>
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
		Bool,
		Number,
		String,
	};



	class Bool
	{
	public:
		Bool( bool boolean ) : mType( Type::Bool ), mValue( boolean ) {}

		Type GetType() const { return mType; }
		lua_Number GetValue() const { return mValue; }

	private:
		Type mType;
		bool mValue;
	};
	class Number
	{
	public:
		Number( lua_Number num ) : mType( Type::Number ), mValue( num ) {}

		Type GetType() const { return mType; }
		lua_Number GetValue() const { return mValue; }

	private:
		Type mType;
		lua_Number mValue;
	};
	class String
	{
	public:
		String( const char* const str ) : mType( Type::String ), mValue( str ) {}

		Type GetType() const { return mType; }
		std::string_view GetValue() const { return mValue; }

	private:
		Type mType;
		std::string mValue;
	};



	using Value = std::variant<Bool, Number, String>;



	Type GetType( const Value& v );
}
