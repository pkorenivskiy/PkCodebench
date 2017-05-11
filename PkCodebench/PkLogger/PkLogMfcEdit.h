#pragma once

#include <ctime>
#include <string>

#include "PkLoggerBase.h"

namespace PkLog
{
	class PkLogMfcEdit final : public PkLoggerBase
	{
	public:
		PkLogMfcEdit() { }
		~PkLogMfcEdit() { }

		virtual void Log(const std::string& msg) override final
		{
			return;

			printf(getTimeStr().c_str());
			printf(": ");
			printf(msg.c_str());
			printf("\n");
		}
	};
}
