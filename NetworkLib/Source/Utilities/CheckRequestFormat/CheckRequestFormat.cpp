#include "pch.h"
#include "CheckRequestFormat.h"

namespace Utilitis::CheckRequestFormat
{
	bool IsValidRequestPattern(const std::regex regex, const char* pksHeaderBuffer)
	{
		std::smatch match;
		std::string str(pksHeaderBuffer);
		return std::regex_search(str, match, regex);
	}
}