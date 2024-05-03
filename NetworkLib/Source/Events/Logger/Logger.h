#pragma once

namespace Logger
{
	enum class Level
	{
		Nothing		= -1,
		Debug		= 0,
		Info		= 1,
		Warning		= 2,
		Error		= 3,
		Critical	= 4,
		Fatal		= 5
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