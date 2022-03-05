#pragma once

#include <functional>

namespace r2
{
	enum class eTestResult;

	class iItem
	{
	public:
		using TitleFunc = std::function<const char*()>;
		using DoFunc = std::function<eTestResult()>;

		virtual ~iItem() {}

		virtual TitleFunc GetTitleFunction() const = 0;
		virtual DoFunc GetDoFunction() = 0;
	};
}