#include "stdafx.h"

#include <cwctype>

#include "Lexilyzer.h"


CLexilyzer::CLexilyzer()
{
}


CLexilyzer::~CLexilyzer()
{
}

bool CLexilyzer::Analyze(const TvLnLexems& lexems)
{
	bool result = true;

	for (size_t i = 0; i < lexems.size(); i++)
	{
		//for (auto it : lexems[i])
		if (lexems[i].size() > 0)
		{
			if (lexems[i][0].Name == L"int")
			{
				processDeclare(lexems[i], i);
			}
			else if (lexems[i][0].Name == L"read")
			{
				processRead(lexems[i], i);
			}
			else if (lexems[i][0].Name == L"write")
			{
				processWrite(lexems[i], i);
			}
			else
			{
				std::wstring sName = L"";
				for (auto n : lexems[i])
					if (!n.Name.empty())
						sName += n.Name + L" ";
				addError(i, sName, L" syntax error.");
			}
		}
	}

	return result;
}

bool CLexilyzer::isTerm(const std::wstring& lex)
{
	bool result = false;

	//result = (m_mLexems.find(lex) != m_mLexems.end());

	return result;
}

bool CLexilyzer::isIdn(const std::wstring& lex) 
{
	bool result = false;

	return result;
}

bool CLexilyzer::isCon(const std::wstring& lex)
{
	bool result = false;

	return result;
}

bool CLexilyzer::isKw(const std::wstring& lex)
{
	return m_mLexems.find(lex) != m_mLexems.end();
}

void CLexilyzer::processDeclare(const std::vector<PkLexema>& lexems, const size_t line)
{
	bool skip = true;
	for (auto it = lexems.begin() + 1; it != lexems.end(); it++)
	{
		skip = !skip;
		if (it->Name == L",")
		{
			if (skip)
				continue;			
			else
				addError(line, it->Name, L" syntax error.");
		}
		else
		{
			if (isKw(it->Name))
			{
				addError(line, it->Name, L" keyword cannot be a variable name.");
			}
			else if (!isVarNameValid(it->Name))
			{
				addError(line, it->Name, L" invalid variable name.");
			}
			else
			{
				if (m_mOutIdn.find(it->Name) != m_mOutIdn.end())
					addError(line, it->Name, L" - redeclaration not allowed.");
				else
					m_mOutIdn[it->Name] = PkOutIdn{ line, it->Name, Integer };
			}
		}
	}
}

void CLexilyzer::processRead(const std::vector<PkLexema>& lexems, const size_t line)
{
	bool skip = true;

	if (lexems[1].Name != L"(")
	{
		addError(line, L"", L"syntax error. missing \"(\".");
		return;
	}
	if (lexems.back().Name != L")")
	{
		addError(line, L"", L"syntax error. missing \")\".");
		return;
	}

	for (auto it = lexems.begin() + 2; it != lexems.end() - 1; it++)
	{
		skip = !skip;
		if (it->Name == L",")
		{
			if (skip)
				continue;
			else
				addError(line, it->Name, L" syntax error.");
		}
		else
		{
			if (isKw(it->Name))
			{
				addError(line, it->Name, L" unexpected token.");
			}
			else if (!isVarNameValid(it->Name))
			{
				addError(line, it->Name, L" invalid variable name.");
			}
			else
			{
				if (m_mOutIdn.find(it->Name) == m_mOutIdn.end())
					addError(line, it->Name, L" - undeclared variable.");
			}
		}
	}
}

void CLexilyzer::processWrite(const std::vector<PkLexema>& lexems, const size_t line)
{
	bool skip = true;

	if (lexems[1].Name != L"(")
	{
		addError(line, L"", L"syntax error. missing \"(\".");
		return;
	}
	if (lexems.back().Name != L")")
	{
		addError(line, L"", L"syntax error. missing \")\".");
		return;
	}

	for (auto it = lexems.begin() + 2; it != lexems.end() - 1; it++)
	{
		skip = !skip;
		if (it->Name == L",")
		{
			if (skip)
				continue;
			else
				addError(line, it->Name, L" syntax error.");
		}
		else
		{
			if (isKw(it->Name))
			{
				addError(line, it->Name, L" unexpected token.");
			}
			else if (!isVarNameValid(it->Name))
			{
				addError(line, it->Name, L" invalid variable name.");
			}
			else
			{
				if (m_mOutIdn.find(it->Name) == m_mOutIdn.end())
					addError(line, it->Name, L" - undeclared variable.");
			}
		}
	}
}

bool CLexilyzer::isVarNameValid(const std::wstring& st)
{
	return (std::iswalpha(st[0]) || st[0] == L'_');
}

void CLexilyzer::addError(size_t nLine, const std::wstring& stoken, const std::wstring& msg)
{
	std::wstring error = L"";
	if (!stoken.empty())
	{
		error += L"\"";
		error += stoken;
		error += L"\" ";
	}
	error += msg;

	if (m_mErrors.find(nLine) == m_mErrors.end())
	{
		m_mErrors.insert(TmErrorsVt(nLine, std::vector<std::wstring>()));
	}

	m_mErrors[nLine].push_back(error);
}

void CLexilyzer::initLexems()
{
	for (auto it : LEXEMS)
	{
		m_mLexems.insert(std::pair<std::wstring, PkLexema>(it.Name, it));
	}
}