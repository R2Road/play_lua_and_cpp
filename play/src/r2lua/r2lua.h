#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

#include "lua_header_package.h"

//
// # REF
// CppCon 2017: Andreas Weis “Howling at the Moon: Lua for C++ Programmers”
// https://www.youtube.com/watch?v=pfwHCiP1HFM
//

namespace r2lua
{
	enum class eType
	{
		Bool,
		Number,
		String,
	};



	class Bool
	{
	public:
		Bool() : mValue( false ) {}
		Bool( bool boolean ) : mValue( boolean ) {}

		static eType GetType() { return eType::Bool; }
		bool GetValue() const { return mValue; }

	private:
		bool mValue;
	};
	class Number
	{
	public:
		Number() : mValue( -1 ) {}
		Number( lua_Number num ) : mValue( num ) {}

		static eType GetType() { return eType::Number; }
		lua_Number GetValue() const { return mValue; }

	private:
		lua_Number mValue;
	};
	class String
	{
	public:
		static constexpr const char* InvalidString = "Invalid String";

		String() : mValue( InvalidString ) {}
		String( const char* const str ) : mValue( str ) {}

		static eType GetType() { return eType::String; }
		std::string_view GetValue() const { return mValue; }

	private:
		std::string mValue;
	};



	using Value = std::variant<Bool, Number, String>;



	eType GetType( const Value& v );
	const char* const GetTypeName( const Value& v );
	const char* const GetTypeName( const eType t );

	//
	// # 20220323 - by R2
	// assert 가 작동할 상황에서도 프로그램을 정상 작동 시키고 싶다면
	// T에 해당하는 타입들에 기본 생성자를 추가해서 반환하면 될 것도 같다.
	// 하지만... 그래야 할까?
	// 나중에 필요할 때 고려해보자.
	//
	// 바로 해버림. @_@
	//
	template<typename T>
	const T& GetValue( const Value& v )
	{
		static_assert(
			std::is_same<T, r2lua::Bool>()
			|| std::is_same<T, r2lua::Number>()
			|| std::is_same<T, r2lua::String>()
		);

		if( const auto* const ret = std::get_if<T>( &v ) )
		{
			return ( *ret );
		}
		else
		{
			static T dummy;
			return dummy;
		}
	}



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



	template<typename... Args>
	ValueVector Call( lua_State* const lua_state_obj, const char* const function_name, Args... args )
	{
		lua_getglobal( lua_state_obj, function_name );
		PushArgs( lua_state_obj, args... );
		lua_pcall( lua_state_obj, sizeof...( args ), LUA_MULTRET, 0 );

		return GetValuesFromStack( lua_state_obj );
	}
}
