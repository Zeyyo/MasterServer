#include "NEtw_pch.h"
#include "ExtensionTable.h"
#include "Events/Exceptions/ExtensionManagerExceptions.h"

namespace ExtensionManager
{
	void RegisterExtensions()
	{
        extensionTable["KuyaYqUrZWDBxdP3Pp"] = "txt";
        extensionTable["kx8XaKdkmEljbZ2exr"] = "jpg";
        extensionTable["oc4T7H2nW9LVpwIUje"] = "png";
        extensionTable["ugKT5g3wMjym4mUrf5"] = "pdf";
        extensionTable["Z7wbjam9ZNVRrX662u"] = "docx";
        extensionTable["WD34Q8RS7jl1UWFDMv"] = "xlsx";
        extensionTable["Rh2IGFKTdVe3zSuAzV"] = "pptx";
        extensionTable["m1r8SsjUVGC7jC2RG4"] = "zip";
	}

    std::string GetExtension(std::string& szKey) {
        auto it = extensionTable.find(szKey);
        if (it != extensionTable.end()) {
            return it->second;
        }
		throw Exceptions::ExtensionManagerExceptions::ExtensionKeyMismatch("");
    }
}