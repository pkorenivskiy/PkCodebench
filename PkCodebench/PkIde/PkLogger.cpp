#include "stdafx.h"
#include "PkLogger.h"

#include <string>

CPkLogger::CPkLogger(COutputList* pEdit)
	:m_pEdit(pEdit)
{
	pEdit->ResetContent();
	pEdit->UpdateData(FALSE);
}

CPkLogger::~CPkLogger()
{
}

void CPkLogger::Log(const std::string& msg)
{
	std::string text = getTimeStr();
	text += ": ";
	text += msg;
	text += "\n";

	m_pEdit->AddString(std::wstring(text.begin(), text.end()).c_str());
	m_pEdit->UpdateData(FALSE);

	if (m_pEdit->GetCount() > 0)
		m_pEdit->SetTopIndex(m_pEdit->GetCount() - 1);
}
