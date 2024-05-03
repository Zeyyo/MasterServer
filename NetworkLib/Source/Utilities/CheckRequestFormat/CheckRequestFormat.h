#pragma once
#include <regex>

namespace Utilitis::CheckRequestFormat
{
	bool IsValidRequestPattern(const std::regex p, std::string pksHeaderBuffer);
	inline std::regex ftpPattern_FileAcquire("^fa ([^/\\\\:*?\"|<>;=,\\[\\]{}~.]{1,50}) (\\d{1,8}) ([a-zA-Z1-9]{18})$");
	inline std::regex ftpPattern_FileDispatch("^fd ([A-Z0-9]{5}-[A-Z0-9]{5}-[A-Z0-9]{5})$");
	inline std::regex ftpPattern_SetupCall("^sc$");

}

