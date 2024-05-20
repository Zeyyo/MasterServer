#pragma once
#include <map>

namespace ExtensionManager
{
	void RegisterExtensions();
	std::string GetExtension(std::string& szKey);
	inline std::map<std::string, std::string> extensionTable;
}
