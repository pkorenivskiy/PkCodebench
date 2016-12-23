#include "stdafx.h"
#include <cwctype>

#include "Syntalizer.h"
#include "PkLangDefs.h"

CSyntalizer::CSyntalizer()
	: CSyntalizer(L"")
{
	m_Errors.push_back(L"not implemented");
}

CSyntalizer::CSyntalizer(const std::wstring& sText)
	: m_sText(sText)
	, m_nPos(-1)
	, m_curState(ReadNexChar)
	, m_curLexema(L"")
	, LOGICALSYM(L"<=>!&")
{
	initLexems();
	initSfm();

	m_Errors.clear();

	for (auto it : m_outLexems)
		it.clear();
	m_outLexems.clear();

	m_outLexems.push_back(std::vector<CPkLexema>());
}

CSyntalizer::~CSyntalizer()
{
}

const TvErrors CSyntalizer::GetErrors() const
{
	return m_Errors;
}

const std::wstring CSyntalizer::GetErrorText() const
{
	std::wstring result;
	for (auto it : m_Errors)
		result += it + L"\n";

	return result;
}

//private functions
void CSyntalizer::initLexems()
{
	for (auto it : LEXEMS)
	{
		m_mLexems.insert(std::pair<std::wstring, CPkLexema>(it.Name, it));
	}
}

void CSyntalizer::initSfm()
{
	/*m_actions[ReadNexChar] = std::bind(&CSyntalizer::readNexChar, this);
	m_actions[NewLine] = std::bind(&CSyntalizer::newLine, this);
	m_actions[ReadyWord] = std::bind(&CSyntalizer::readyWord, this);*/
}

// SFM fuinctions
void CSyntalizer::processChar()
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
			m_curState = StartConst;
		else
			m_curState = ReadNexChar;
		
		m_curLexema.push_back(ch);
	}
	else if (std::iswalpha(ch) || ch == L'_')
	{
		if (m_curState == StartConst)
			m_curState = InvalidLexema;

		m_curLexema.push_back(ch);
	}
	else if (ch == L'=')
	{
		if (m_curState == StartConst || m_curLexema)
	}
}

void CSyntalizer::processLexema()
{

}