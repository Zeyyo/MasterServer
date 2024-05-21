#pragma once

namespace Logger
{
	enum class Level
	{
        /// <summary>
        /// Shall represent no logging
        /// </summary>
        Nothing = -1,

        /// <summary>
        /// Shall represent detailed debug information
        /// </summary>
        Debug = 0,

        /// <summary>
        /// Shall represent general informational messages
        /// </summary>
        Info = 1,

        /// <summary>
        /// Shall represent warnings indicating a potential issue
        /// </summary>
        Warning = 2,

        /// <summary>
        /// Shall represent an error that is not considered critical 
        /// and will not result in data loss
        /// </summary>
        Error = 3,

        /// <summary>
        /// Shall represent an issue, which will result in closing 
        /// the connection
        /// </summary>
        Critical = 4,

        /// <summary>
        /// Shall represent an issue, which will result in shutting 
        /// down the server
        /// </summary>
        Fatal = 5
	};

	struct EndlT {};
	struct FlushT {};

	const EndlT endl;
	const FlushT flush;

	class ILogger
	{
	public:
		virtual ~ILogger() = default;

		virtual Level Filter() const = 0;
		virtual void SetFilter(Level aLevel) = 0;

		virtual ILogger& operator[](Level aLevel) = 0;
		virtual ILogger& operator<<(std::string const& szMessage) = 0;
		virtual ILogger& operator<<(EndlT) = 0;
		virtual ILogger& operator<<(FlushT) = 0;
	protected:
		const std::string debugPrefix = "[DEBUG] ";
		const std::string infoPrefix = "[INFO] ";
		const std::string warningPrefix = "[WARNING] ";
		const std::string errorPrefix = "[ERROR] ";
		const std::string criticalPrefix = "[CRITICAL] ";
		const std::string fatalPrefix = "[FATAL] ";
	};
}