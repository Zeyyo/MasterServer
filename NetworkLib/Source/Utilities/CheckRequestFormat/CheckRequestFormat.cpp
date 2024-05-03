#include "NEtw_pch.h"

#include <string>
#include "CheckRequestFormat.h"

namespace Utilitis::CheckRequestFormat
{
	bool IsValidRequestPattern(const std::regex regex, std::string pksHeaderBuffer)
	{
		std::smatch match;
		return std::regex_search(pksHeaderBuffer, match, regex);
	}
}