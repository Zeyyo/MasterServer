#pragma once
#include "Includes/Types/Time.h"
#include "Includes/Filters.h"

namespace Utilities::NameMangling
{
	using NetworkLibrary::TimeFormat;
	void SuffixMangle(std::string& szBody);
}