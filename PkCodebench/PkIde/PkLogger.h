#pragma once

#include "../PkLogger/PkLoggerBase.h"
#include "OutputWnd.h"

class CPkLogger : public PkLog::PkLoggerBase
{
public:
	CPkLogger(COutputList* pEdit);
	virtual ~CPkLogger();

	virtual void Log(const std::string& msg);

private:
	COutputList* m_pEdit;
};

