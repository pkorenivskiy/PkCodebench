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
		m_actions[m_curState]();
	}

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
	m_actions[ConstLexema] = std::bind(&CSyntalyzer::constLexema, this);
	m_actions[InvalidLexema] = std::bind(&CSyntalyzer::invalidLexema, this);
}

// SFM fuinctions
void CSyntalyzer::processChar()
{
	if (m_nPos >= m_sText.length())
		m_curState = Final;

	wchar_t ch = m_sText[++m_nPos];

	if (std::iswspace(ch))
	{
		if (ch == L'\n' || ch == L'\r')
			m_curState = NewLine;
		else
			m_curState = ReadyLexema;
	}
	else if (std::iswdigit(ch))
	{
		if (m_curLexema.empty())
			m_curState = ConstLexema;
		else
			m_curState = ReadNexChar;
		
		m_curLexema.push_back(ch);
	}
	else if (std::iswalpha(ch) || ch == L'_')
	{
		if (m_curState == ConstLexema)
			m_curState = InvalidLexema;

		m_curLexema.push_back(ch);
	}
	else if (LOGICALSYM.find(ch) != std::wstring::npos)
	{
		if (m_curState == ConstLexema || m_curLexema.empty() == false)
		{
			// hack 
			//processLexema();
			
			m_curState = ReadyLexema;
			// костыль
			m_nPos--;
		}
		else
			m_curLexema.push_back(ch);
	}
	else if (ch == L',')
	{
		if (m_curLexema.empty() == false)
			m_nPos--;
		else
			m_curLexema.push_back(ch);

		m_curState = ReadyLexema;
	}
	else if (ch == L':')
	{
		if (m_curState == ConstLexema || m_curLexema.empty() == true)
			m_curState = InvalidLexema;

		m_curLexema.push_back(ch);
	}
	else if (OPERATORS.find(ch) != std::wstring::npos)
	{
		if (m_curLexema.empty() == false)
		{
			m_curState = ReadyLexema;
			m_nPos--;
		}
		else
		{
			m_curLexema.push_back(ch);
		}
	}
	else
	{
		m_curState = InvalidLexema;
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

		m_outLexems.end()->push_back(PkLexema{ m_curLexema });
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
	processLexema();

	wchar_t err[512];
	swprintf_s(err, 512, L"Line %d. Syntax error. Unknown lexema %s", m_nLine, m_curLexema.c_str());
	m_Errors.push_back(err);
}

void CSyntalyzer::processNewLine()
{
	if (m_outLexems.end()->empty() == false)
		m_outLexems.push_back(std::vector<PkLexema>());
}
