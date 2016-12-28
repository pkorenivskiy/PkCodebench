#include "stdafx.h"

#include <cwctype>
#include <algorithm>  

#include "Lexilyzer.h"


CLexilyzer::CLexilyzer()
	: LOGICALSYM(L"<=>!&")
	, OPERATORS(L"+-*/^")
{
	initLexems();
}


CLexilyzer::~CLexilyzer()
{
}

bool CLexilyzer::Analyze(const TvLnLexems& lexems)
{
	clearResult();

	for (size_t i = 0; i < lexems.size(); i++)
		validate(lexems[i], i);

	return m_mErrors.empty();
}

size_t CLexilyzer::validate(const std::vector<PkLexema>& lnLexems, size_t line, size_t start)
{
	bool result = 0;	

	if (lnLexems.empty())
		return 0;

	for (auto& it = lnLexems.begin() + start; it != lnLexems.end(); it++, result++)
	{
		if (it->Name == L"int")
		{
			processDeclare(lnLexems, line, 1);
		}
		else if (it->Name == L"read")
		{
			processRead(lnLexems, line);
		}
		else if (it->Name == L"write")
		{
			processWrite(lnLexems, line);
		}
		else if (it->Name == L"for")
		{
			processFor(lnLexems, line);
		}
		else
		{
			std::wstring sName = L"";
			for (auto n : lnLexems)
				if (!n.Name.empty())
					sName += n.Name + L" ";
			addError(line, sName, L" syntax error.");
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
	bool result = m_mOutIdn.find(lex) == m_mOutIdn.end();

	return result;
}

bool CLexilyzer::isCon(const std::wstring& lex)
{
	bool result = false;

	int nVal = _wtoi(lex.c_str());

	if (std::find_if(m_vOutConst.begin(), m_vOutConst.end(), [&nVal](const PkOutConst& o) {return o.Value == nVal; }) == m_vOutConst.end())
	{
		if (!lex.empty() && std::iswdigit(lex[0]))
		{
			m_vOutConst.push_back(PkOutConst{ m_vOutConst.size(), nVal });
		}
	}

	return result;
}

bool CLexilyzer::isKw(const std::wstring& lex)
{
	return m_mLexems.find(lex) != m_mLexems.end();
}

void CLexilyzer::processDeclare(const std::vector<PkLexema>& lexems, const size_t line, size_t start)
{
	bool skip = true;
	for (auto it = lexems.begin() + start; it != lexems.end(); it++)
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

void CLexilyzer::processRead(const std::vector<PkLexema>& lexems, const size_t line, size_t start)
{
	bool skip = true;

	if (lexems.size() < 3)
		return;

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

void CLexilyzer::processWrite(const std::vector<PkLexema>& lexems, const size_t line, size_t start)
{
	bool skip = true;

	if (lexems.size() < 3)
		return;

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

void CLexilyzer::processFor(const std::vector<PkLexema>& lexems, const size_t line, size_t start)
{	
	ForStates state = Init;
	for (auto& it = lexems.begin() + start; it != lexems.end(); it++)
	{
		switch (state)
		{
		case Init:
			if (it->Name != L"for")
				addError(line, it->Name, L"Unexpected token.");
			state = Expr;
			break;
		case Expr:
			if (isIdn((++it)->Name) && (++it)->Name == L"=")
			{
				processExpr(lexems, line, lexems.end() - it);
				state = By;
			}
			else
			{
				addError(line, L"", L" syntax error. Missed expression.");
			}
			break;
		case By:
			if (it->Name != L"by")
				addError(line, it->Name, L"Unexpected token. Expected \"by\".");
			state = LExpr;
			break;
		case LExpr:
			//processLExpr();
			state = Do;
			break;
		case Do:
			if (it->Name != L"do")
				addError(line, it->Name, L"Unexpected token. Expected \"by\".");
			else
				validate(lexems, line, it - lexems.begin() + 1);
			break;
		default:			
			break;
		}
	}
}

size_t CLexilyzer::processExpr(const std::vector<PkLexema>& lexems, const size_t line, size_t start)
{
	size_t result = 0;

	size_t state = 0;

	for (auto& it = lexems.begin() + start; it != lexems.end(); it++, result++)
	{
		// hack - break if by while do
		if (it->Name == L"by" || it->Name == L"while" || it->Name == L"do")
			break;

		switch (state)
		{
		case 0: //init
			if (it->Name == L"-")
				state = 1;
			else if ()
			break;
		case 1: // unary minus
			if (!(isIdn(it->Name) || isCon(it->Name)))
			{
				addError(line, it->Name, L" undeclared identifier.");
				state = -1; // finite la 
			}
			else
				state = 1;
			break;
		case 2: // math
			if (OPERATORS.find(it->Name) == std::string::npos)
			{
				addError(line, L"", L" syntax error");
				state = -1;
			}
			else
				state = 1;
			break;
		default:
			break;
		}

		

		it++; result++;
		while (it != lexems.end())
		{
			if (it->Name == L"")

		}
	}

	return result;
}

void CLexilyzer::clearResult()
{
	m_nLine = 0;
	m_vOutLex.clear();
	m_vOutConst.clear();
	m_mOutIdn.clear();

	m_mErrors.clear();
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