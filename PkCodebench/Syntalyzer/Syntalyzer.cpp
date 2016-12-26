#include "stdafx.h"
#include <cwctype>

#include "Syntalyzer.h"
#include "PkLangDefs.h"

CSyntalyzer::CSyntalyzer()
	: CSyntalyzer(L"")
{
	m_Errors.push_back(L"not implemented");
}

CSyntalyzer::CSyntalyzer(const std::wstring& sText)
	: m_sText(sText)
	, m_nPos(-1)
	, m_nLine(1)
	, m_curState(ReadNexChar)
	, m_curLexema(L"")
	, LOGICALSYM(L"<=>!&")
	, OPERATORS(L"+-*/^")
{
	initLexems();
	initSfm();

	m_Errors.clear();

	for (auto it : m_outLexems)
		it.clear();
	m_outLexems.clear();

	m_outLexems.push_back(std::vector<PkLexema>());
}

CSyntalyzer::~CSyntalyzer()
{
}

const TvErrors CSyntalyzer::GetErrors() const
{
	return m_Errors;
}

const std::wstring CSyntalyzer::GetErrorText() const
{
	std::wstring result;
	for (auto it : m_Errors)
		result += it + L"\n";

	return result;
}

const TvLnLexems CSyntalyzer::Analyze()
{
	m_curState = ReadNexChar;

	while (m_curState != Final)
	{
		//m_actions[m_curState]();
		processChar();
	}

	if (m_curLexema.empty() == false)
		processLexema();

	if (m_outLexems.back().empty())
		m_outLexems.pop_back();

	return m_outLexems;
}

//private functions
void CSyntalyzer::initLexems()
{
	for (auto it : LEXEMS)
	{
		m_mLexems.insert(std::pair<std::wstring, PkLexema>(it.Name, it));
	}
}

void CSyntalyzer::initSfm()
{
	m_actions[ReadNexChar] = std::bind(&CSyntalyzer::processChar, this);
	m_actions[NewLine] = std::bind(&CSyntalyzer::processNewLine, this);
	m_actions[ReadyLexema] = std::bind(&CSyntalyzer::processLexema, this);
	m_actions[CON] = std::bind(&CSyntalyzer::constLexema, this);
	m_actions[InvalidLexema] = std::bind(&CSyntalyzer::invalidLexema, this);
}

// SFM functions
void CSyntalyzer::processChar()
{
	if (++m_nPos >= m_sText.length() && m_nPos != -1)
	{
		m_curState = Final;
		return;
	}

	wchar_t ch = m_sText[m_nPos];

	if (m_curState == ReadNexChar)
	{
		if (std::iswspace(ch))
		{
			if (ch == L'\n' || ch == L'\r')
				m_curState = NewLine;
		}
		else if (std::iswdigit(ch))
		{
			m_curState = CON;		
			m_curLexema.push_back(ch);
		}
		else if (std::iswalpha(ch) || ch == L'_')
		{
			m_curState = TRM;
			m_curLexema.push_back(ch);
		}
		else if (LOGICALSYM.find(ch) != std::wstring::npos || OPERATORS.find(ch) != std::wstring::npos)
		{
			m_curState = OPR;
			m_curLexema.push_back(ch);
		}
		else if (ch == L',')
		{
			m_curLexema.push_back(ch);
			processLexema();
		}
		else if (ch == L'(' || ch == L')')
		{
			m_curLexema.push_back(ch);
			processLexema();
		}
		else
		{
			m_curLexema.push_back(ch);
			m_curState = InvalidLexema;
		}
	}
	else if (m_curState == NewLine)
	{
		if (ch != L'\n' && ch != L'\r')
			processNewLine();
	}
	else if (m_curState == TRM)
	{
		if (std::iswspace(ch) 
			|| LOGICALSYM.find(ch) != std::string::npos 
			|| OPERATORS.find(ch) != std::string::npos
			|| ch == L','
			|| ch == L'(' || ch == L')')
		{
			processLexema();
			if (std::iswspace(ch) == false)
				m_nPos--;
		}
		else
			m_curLexema.push_back(ch);
	}
	else if (m_curState == IDN)
	{

	}
	else if (m_curState == CON)
	{
		if (std::iswspace(ch)
			|| LOGICALSYM.find(ch) != std::string::npos
			|| OPERATORS.find(ch) != std::string::npos)
		{
			processLexema();
			m_nPos--;
		}
		else if (std::iswdigit(ch))
		{
			m_curLexema.push_back(ch);
		}
		else
		{
			m_curLexema.push_back(ch);
			m_curState = InvalidLexema;
		}
	}
	else if (m_curState == OPR)
	{
		if (std::iswspace(ch))
		{
			processLexema();
		}
		else if (std::iswalpha(ch) || std::iswdigit(ch))
		{
			processLexema();
			m_nPos--;
		}
		else
		{
			m_curLexema.push_back(ch);
		}
	}
	else if (m_curState == InvalidLexema)
	{
		if (std::iswspace(ch)
			|| LOGICALSYM.find(ch) != std::string::npos
			|| OPERATORS.find(ch) != std::string::npos)
		{
			invalidLexema();
			m_nPos--;
		}

		if (!std::iswspace(ch))
			m_curLexema.push_back(ch);
	}
}

void CSyntalyzer::processLexema()
{
	if (m_curLexema.empty() == false)
	{
		PkLexema lexema { m_curLexema };
		
		auto it = m_mLexems.find(m_curLexema);
		if (it != m_mLexems.end())
		{
			lexema = it->second;
		}

		m_outLexems.back().push_back(lexema);
	}

	m_curLexema.clear();

	m_curState = ReadNexChar;
}

void CSyntalyzer::constLexema()
{
	m_curState = ReadNexChar;
}

void CSyntalyzer::invalidLexema()
{
	wchar_t err[512];
	swprintf_s(err, 512, L"Line %d. Syntax error. Unknown lexema \"%s\"", m_nLine, m_curLexema.c_str());
	m_Errors.push_back(err); 
	
	processLexema();
}

void CSyntalyzer::processNewLine()
{
	if (m_curLexema.empty() == false)
		processLexema();

	if (m_outLexems.back().empty() == false)
		m_outLexems.push_back(std::vector<PkLexema>());

	m_nPos--;
	m_curState = ReadNexChar;
}
