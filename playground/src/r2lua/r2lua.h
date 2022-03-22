#pragma once

#include <string>
#include <string_view>
#include <variant>
#include <vector>

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
		Bool( bool boolean ) : mValue( boolean ) {}

		static Type GetType() { return Type::Bool; }
		lua_Number GetValue() const { return mValue; }

	private:
		bool mValue;
	};
	class Number
	{
	public:
		Number( lua_Number num ) : mValue( num ) {}

		static Type GetType() { return Type::Number; }
		lua_Number GetValue() const { return mValue; }

	private:
		lua_Number mValue;
	};
	class String
	{
	public:
		String( const char* const str ) : mValue( str ) {}

		static Type GetType() { return Type::String; }
		std::string_view GetValue() const { return mValue; }

	private:
		std::string mValue;
	};



	using Value = std::variant<Bool, Number, String>;



	Type GetType( const Value& v );



	void Push( lua_State* const lua_state_obj, bool b );
	void Push( lua_State* const lua_state_obj, int n );
	void Push( lua_State* const lua_state_obj, lua_Number n );
	void Push( lua_State* const lua_state_obj, const char* const str );

	template<typename... Args>
	void PushArgs( lua_State* const lua_state_obj, Args... args )
	{
		( Push( lua_state_obj, args ), ... );
	}

	r2lua::Value GetValueFromStack( lua_State* const lua_state_obj, int index );

	using ValueVector = std::vector<r2lua::Value>;
	r2lua::ValueVector GetValuesFromStack( lua_State* const lua_state_obj );
}
