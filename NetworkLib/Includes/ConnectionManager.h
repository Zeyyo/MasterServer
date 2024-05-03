#pragma once
#include <sal.h>
#include "Includes/Types/HandlerModule.h"

namespace NetworkLibrary
{
    /// <summary>
    /// Manages incoming connections, creates session objects for each connection,
    /// and adds them to a session queue for further processing.
    /// </summary>
    class ConnectionManager
    {
    public:
        /// <summary>
        /// Constructs a ConnectionManager object with the specified module type handler flags.
        /// </summary>
        /// <param name="handlerFlags">Flags indicating the type of module handlers to manage.</param>
        ConnectionManager(_In_ ModuleType handlerFlags);

        /// <summary>
        /// Adds an individual session handler identified by the given flags.
        /// </summary>
        /// <param name="handlerFlags">Flags identifying the session handler to add.</param>
        void AddIndividualSessionHandler(_In_ int handlerFlags);

        /// <summary>
        /// Removes an individual session handler identified by the given flags.
        /// </summary>
        /// <param name="handlerFlags">Flags identifying the session handler to remove.</param>
        void RemoveIndividualSessionHandler(_In_ int handlerFlags);

    private:
        /// <summary>
        /// Initializes the ConnectionManager, setting up necessary components and configurations.
        /// </summary>
        void InitializeConnectionManager();
    };
}