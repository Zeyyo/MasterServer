#include "NEtw_pch.h"

#include <iomanip>
#include <ctime>
#include <sstream>

#include "NameMangling.h"

namespace Utilities::NameMangling
{
    std::string GetSuffix()
    {
        time_t time = std::time(nullptr);
        tm tm;
        localtime_s(&tm ,&time);
        std::ostringstream oss;
        if (Filters::timeFormatFilter == TimeFormat::DATE)
            oss << std::put_time(&tm, "%d-%m-%Y");
        if (Filters::timeFormatFilter == TimeFormat::TIME)
            oss << std::put_time(&tm, "%H-%M-%S");
        if (Filters::timeFormatFilter == TimeFormat::DATE_TIME)
            oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
        auto suffix = oss.str();

        return suffix;
    }

	void SuffixMangle(std::string& szBody)
	{
        std::string suffix = GetSuffix();
        std::string szResult = szBody + "-" + suffix;
        szBody = szResult;
	}
}