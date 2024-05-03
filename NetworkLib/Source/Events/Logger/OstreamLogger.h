#pragma once
#include "NEtw_pch.h"
#include <ostream>
#include "Logger.h"

namespace Logger
{

	template<typename CharT, typename Traits = std::char_traits<CharT>>
	class OstreamLogger : public ILogger
	{
	public:
		OstreamLogger(std::basic_ostream<CharT, Traits>& aStream) : iStream{ aStream }
		{ }

		Level Filter() const override
		{
			return iFilterLevel;
		}
		void SetFilter(Level aLevel) override
		{
			iFilterLevel = aLevel;
		}

		ILogger& operator[](Level aLevel) override
		{
			IMessageLevel = aLevel;

			if (IMessageLevel == Level::Debug)
				iStream << debugPrefix;
			if (IMessageLevel == Level::Warning)
				iStream << warningPrefix;
			if (IMessageLevel == Level::Info)
				iStream << infoPrefix;
			if (IMessageLevel == Level::Error)
				iStream << errorPrefix;
			if (IMessageLevel == Level::Critical)
				iStream << criticalPrefix;
			if (IMessageLevel == Level::Fatal)
				iStream << fatalPrefix;

			return *this;
		}
		ILogger& operator<<(std::string const& szMessage) override
		{
			if (IMessageLevel >= iFilterLevel)
				iStream << szMessage;

			return *this;
		}
		ILogger& operator<<(EndlT) override
		{
			if (IMessageLevel >= iFilterLevel)
				iStream << std::endl;
			return *this;
		}
		ILogger& operator<<(FlushT) override
		{
			if (IMessageLevel >= iFilterLevel)
				iStream << std::flush;
			return *this;
		}
	private:
		std::basic_ostream<CharT, Traits>& iStream;
		Level iFilterLevel = Level::Info;
		Level IMessageLevel = Level::Fatal;
	};

	using OstreamLog = OstreamLogger<char>;
	inline Logger::OstreamLog LOG{ std::cout };

}