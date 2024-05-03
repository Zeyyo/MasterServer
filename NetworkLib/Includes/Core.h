#pragma once
#include <sal.h>

namespace NetworkLibrary
{
	/// <summary>
	/// Initializes and manages the core compont of the server necessary for the application's operation.
	/// This class is responsible for setting up the Windows Sockets API with the specified version.
	/// It encapsulates the initialization of core functionalities and ensures that the Windows Sockets
	/// environment is correctly prepared for network operations.
	/// </summary>
	class Core
	{
	public:
		/// <summary>
		/// Constructs a Core object and initializes the core components necessary for application operation,
		/// including the initialization of the Windows Sockets API.
		/// </summary>
		/// <param name="version">Specifies the version of the Windows Sockets API that the application 
		/// intends to use. This is passed to the InitializeCore method which configures the necessary components.</param>
		Core(_In_ WORD version)
		{
			InitializeCore(version);
		}
	private:
		/// <summary>
		/// Attempts to initialize the core components of the application by forwarding the initialization
		/// call to relevant subsystems. This method also includes error handling to manage exceptions
		/// that may arise during the initialization process.
		/// </summary>
		/// <param name="version">Specifies the version of the core components to initialize, guiding the
		/// configuration and ensuring compatibility across system functionalities.</param>
		void InitializeCore(WORD version);
		/// <summary>
		/// Initializes the Windows Sockets API (Winsock) with the specified version, setting up the network 
		/// communication capabilities required by the application.
		/// </summary>
		/// <param name="version">Specifies the version of the Windows Sockets API that the application 
		/// intends to use, ensuring proper initialization of network functionalities.</param>
		void InitializeWinsock(WORD version);
		/// <summary>
		/// Represents the structure that stores information about the Windows Sockets implementation.
		/// This structure is used to initialize and manage the Windows Sockets environment within the application.
		/// </summary>
		WSADATA wsaData_;
		/// <summary>
		/// Stores the result of Windows Sockets API calls or system functions related to network operations.
		/// This variable is utilized to capture and handle the outcome of network-related operations within the application.
		/// </summary>
		DWORD dwResult;
	};
}
