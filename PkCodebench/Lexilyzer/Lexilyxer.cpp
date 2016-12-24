#include "stdafx.h"

#include <cwctype>

#include "Lexilyxer.h"


CLexilyxer::CLexilyxer()
{
}


CLexilyxer::~CLexilyxer()
{
}

bool CLexilyxer::Analyze(const TvLnLexems& lexems)
{
	for (size_t i = 0; i < lexems.size(); i++)
	{
		for (auto it : lexems[i])
		{
			if (isTerm(it.Name))
			{
				processDeclare(lexems[i], i);
			}
		}
	}
}

bool CLexilyxer::isTerm(const std::wstring& lex)
{
	bool result = false;

	return result;
}

bool CLexilyxer::isIdn(const std::wstring& lex) 
{
	bool result = false;

	return result;
}

bool CLexilyxer::isCon(const std::wstring& lex)
{
	bool result = false;

	return result;
}

bool CLexilyxer::isKw(const std::wstring& lex)
{
	return m_mLexems.find(lex) == m_mLexems.end();
}

void CLexilyxer::processDeclare(const std::vector<PkLexema>& lexems, const size_t line)
{
	bool skip = true;
	for (auto it = lexems.begin() + 1; it != lexems.end(); it++)
	{
		skip != skip;
		if (it->Name == L",")
		{
			if (skip)
				continue;			
			else
				m_mErrors.insert(std::pair<size_t, std::wstring>(line, it->Name + L" syntax error."));
		}
		else
		{
			if (isKw(it->Name) || std::iswalpha(it->Name[1]))
			{
				m_mErrors.insert(std::pair<size_t, std::wstring>(line, it->Name + L" invalid declaration."));
			}
			else
			{
				if (m_mOutIdn.find(it->Name) != m_mOutIdn.end())
					m_mErrors.insert(std::pair<size_t, std::wstring>(line, it->Name + L" - redeclaration not allowed."));
				m_mOutIdn[it->Name] = PkOutIdn{ line, it->Name, Integer };
			}
		}
	}
}

void CLexilyxer::initLexems()
{
	for (auto it : LEXEMS)
	{
		m_mLexems.insert(std::pair<std::wstring, PkLexema>(it.Name, it));
	}
}