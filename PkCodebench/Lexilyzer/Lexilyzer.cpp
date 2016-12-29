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

bool CLexilyzer::Analyze(TvLexLines& lexems)
{
	clearResult();

	for (size_t i = 0; i < lexems.size(); i++)
		validate(lexems[i], i);

	return m_mErrors.empty();
}

size_t CLexilyzer::validate(std::vector<PkLexema>& lnLexems, size_t line, size_t start)
{
	bool result = 0;	

	if (lnLexems.empty())
		return 0;

	m_itLine = lnLexems.begin() + start;

	while (m_itLine != lnLexems.end())
	{
		if (m_itLine->Name == L"int" || m_itLine->Name == L"label")
		{
			auto idnType = m_itLine->Name == L"int" ? Int : Lbl;
			processDeclare(lnLexems, idnType, line);
		}
		else if (m_itLine->Name == L"read")
		{
			processRead(lnLexems, line);
		}
		else if (m_itLine->Name == L"write")
		{
			processWrite(lnLexems, line);
		}
		else if (m_itLine->Name == L"for")
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
			break;
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

void CLexilyzer::processDeclare(const std::vector<PkLexema>& lexems, IdnTypes idnType, const size_t line)
{
	bool skip = true;
	
	while (++m_itLine != lexems.end())
	{
		skip = !skip;
		if (m_itLine->Name == L",")
		{
			if (skip)
				continue;			
			else
				addError(line, m_itLine->Name, L" syntax error.");
		}
		else
		{
			if (isKw(m_itLine->Name))
			{
				addError(line, m_itLine->Name, L" keyword cannot be a variable name.");
			}
			else if (!isVarNameValid(m_itLine->Name))
			{
				addError(line, m_itLine->Name, L" invalid variable name.");
			}
			else
			{
				if (m_mOutIdn.find(m_itLine->Name) != m_mOutIdn.end())
					addError(line, m_itLine->Name, L" - redeclaration not allowed.");
				else
					m_mOutIdn[m_itLine->Name] = PkOutIdn{ line, m_itLine->Name, idnType };
			}
		}
	}
}

void CLexilyzer::processRead(const std::vector<PkLexema>& lexems, const size_t line)
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

	m_itLine++;
	while(++m_itLine != lexems.end() - 1)
	{
		skip = !skip;
		if (m_itLine->Name == L",")
		{
			if (skip)
				continue;
			else
				addError(line, m_itLine->Name, L" syntax error.");
		}
		else
		{
			if (isKw(m_itLine->Name))
			{
				addError(line, m_itLine->Name, L" unexpected token.");
			}
			else if (!isVarNameValid(m_itLine->Name))
			{
				addError(line, m_itLine->Name, L" invalid variable name.");
			}
			else
			{
				if (m_mOutIdn.find(m_itLine->Name) == m_mOutIdn.end())
					addError(line, m_itLine->Name, L" - undeclared variable.");
			}
		}
	}
	m_itLine++; // skip end ")"
}

void CLexilyzer::processWrite(const std::vector<PkLexema>& lexems, const size_t line)
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

	m_itLine++;
	while(++m_itLine != lexems.end() - 1)
	{
		skip = !skip;
		if (m_itLine->Name == L",")
		{
			if (skip)
				continue;
			else
				addError(line, m_itLine->Name, L" syntax error.");
		}
		else
		{
			if (isKw(m_itLine->Name))
			{
				addError(line, m_itLine->Name, L" unexpected token.");
			}
			else if (!isVarNameValid(m_itLine->Name))
			{
				addError(line, m_itLine->Name, L" invalid variable name.");
			}
			else
			{
				if (m_mOutIdn.find(m_itLine->Name) == m_mOutIdn.end())
					addError(line, m_itLine->Name, L" - undeclared variable.");
			}
		}
	}
	m_itLine++; // skip end ")"
}

void CLexilyzer::processFor(std::vector<PkLexema>& lexems, const size_t line)
{	
	ForStates state = Init;
	while(m_itLine != lexems.end())
	{
		switch (state)
		{
		case Init:
			if (m_itLine->Name != L"for")
				addError(line, m_itLine->Name, L"Unexpected token.");
			state = Expr;
			break;
		case Expr:
			if (isIdn((++m_itLine)->Name) && (++m_itLine)->Name == L"=")
			{
				processExpr(lexems, line, lexems.end() - m_itLine);
				state = By;
			}
			else
			{
				addError(line, L"", L" syntax error. Missed expression.");
			}
			break;
		case By:
			if (m_itLine->Name != L"by")
				addError(line, m_itLine->Name, L"Unexpected token. Expected \"by\".");
			state = LExpr;
			break;
		case LExpr:
			//processLExpr();
			state = Do;
			break;
		case Do:
			if (m_itLine->Name != L"do")
				addError(line, m_itLine->Name, L"Unexpected token. Expected \"by\".");
			else
				validate(lexems, line, m_itLine - lexems.begin() + 1);
			break;
		default:			
			break;
		}

		m_itLine++;
	}
}

size_t CLexilyzer::processExpr(const std::vector<PkLexema>& lexems, const size_t line, size_t start)
{
	size_t result = 0;

	size_t state = 0;

	for (auto& it = lexems.begin() + start; it != lexems.end(); it++, result++)
	{
		switch (state)
		{
		case 0: //init
			if (it->Name == L"-")
				state = 1;
			//else if ()
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