#pragma once

//#include <iostream>
#include <ctime>
#include <string>

#include "PkLoggerBase.h"

namespace PkLog
{
	class PkLogConsole final : public PkLoggerBase
	{
	public:
		PkLogConsole() { }
		~PkLogConsole() { }

		virtual void Log(const std::string& msg) override final
		{
			printf(getTimeStr().c_str());
			printf(": ");
			printf(msg.c_str());
			printf("\n");
		}
	};
}
