#pragma once

#include <string>

namespace PkLog
{
	class PkLoggerBase
	{
	public:
		PkLoggerBase() { }
		virtual ~PkLoggerBase() { }

		virtual void Log(const std::string& msg) = 0;
	
	protected:
		const std::string getTimeStr()
		{
			time_t rawtime;
			struct tm timeinfo;
			char buffer[80];

			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);

			strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);
			return std::string(buffer);
		}
	};
}
