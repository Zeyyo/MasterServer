#pragma once
#include "pch.h"
#include <string>
#include <regex>

namespace Utilitis::CheckRequestFormat
{
	bool ValidateRequestPattern(const std::regex p, const char* pksHeaderBuffer);
	inline std::regex FTPPattern("(\\w+),(\\w+),([A-Z]{2}[0-9]{3}[A-Z]{2})");

}

