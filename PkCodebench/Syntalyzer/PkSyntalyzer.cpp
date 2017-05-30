#include "stdafx.h"
#include "PkSyntalyzer.h"

#include <memory>
#include <string>

#include "PkBaseAnalyzer.h"
#include "PkDeclAnalyzer.h"
#include "PkExprAnalyzer.h"

using namespace PkLang;

PkSyntalyzer::PkSyntalyzer(const TmPkOutLexems& lexems, const TvPkOutIdnts& idents, const TmPkOutConsts& consts)
	: m_nLine(0)
	, m_nIndex(0)
	, m_lexems(lexems)
	, m_idents(idents)
	, m_consts(consts)
{
}

PkSyntalyzer::~PkSyntalyzer()
{
}


bool PkSyntalyzer::Analyze()
{
	bool res = false;

	for (auto& line : m_lexems)
	{
		if (line.second.empty())
			continue;

		bool isError = false;
		m_nLine = line.second[0].Line;
		m_nIndex = 0;		
		m_line = line.second;

		if (line.second[0].Id == LNG_INT || line.second[0].Id == LNG_LABEL)
			res |= chkDecl();
		else if (line.second[0].Id == LNG_IF)
			res |= chkIf();
		else if (line.second[0].Id == LNG_FOR)
			res |= chkFor();
		else if (line.second[0].Id == LNG_READ)
			res |= chkRead();
		else if (line.second[0].Id == LNG_WRITE)
			res |= chkWrite();
		else if (line.second[0].Class == PkLexemClasses::IDN)
			res |= chkExpr();
		else
		{
			addError(L"Syntax error ");
			res = false;
		}
	}

	return res;
}

// private methods

bool PkSyntalyzer::chkDecl()
{
	bool res = false;

	if (m_line.size() < 2)
	{
		addError(L"Missed identifiers.");
		return res;
	}

	PkIdnTypes identType = PkIdnTypes::Int;
	if (m_line[0].Id == LNG_INT)
		identType = PkIdnTypes::Int;
	else if (m_line[0].Id == LNG_LABEL)
		identType = PkIdnTypes::Lbl;
	else
	{
		addError(L"Syntax error.");
		return res;
	}

	auto expClass = PkLexemClasses::IDN;

	for (auto& ident = m_line.begin() + m_nIndex + 1; ident != m_line.end(); ident++)
	{
		if (ident->Class != expClass)
		{
			addError(L"Syntax error.");
			return res;
		}

		if (expClass == PkLexemClasses::IDN)
		{
			if (ident->Class == PkLexemClasses::IDN)
			{
				auto& itId = std::find(m_idents.begin(), m_idents.end(), ident->Index);

				if (itId != m_idents.end())
					itId->Type = identType;
				else
					addError(L"Unknown identifier.");
			}
			else
			{
				addError(L"Identifier expected.");
				return res;
			}
		}
		else
		{
			if (ident->Id != LNG_CMA)
			{
				addError(L"Comma expected.");
				return res;
			}
		}

		expClass = expClass == PkLexemClasses::IDN ? PkLexemClasses::TRM : PkLexemClasses::IDN;
	}

	res = true;

	return res;
}

bool PkSyntalyzer::chkListIDN()
{
	bool res = false;
	return res;
}

bool PkSyntalyzer::chkRead()
{
	bool res = false;

	if (m_line[m_nIndex++].Id == LNG_READ)
	{
		if (checkIndex() && m_line[m_nIndex++].Id == LNG_LBR)
		{
			if (checkIndex() && m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex++) == PkIdnTypes::Int)
			{
				if (checkIndex() && m_line[m_nIndex++].Id == LNG_RBR)
				{
					if (checkIndex() == false)
					{
						res = true;
					}
					else
					{
						addError(L"Unexpected end of line");
					}
				}
				else
				{
					addError(L"Expected \")\" keyword");
				}
			}
			else
			{
				addError(L"Missing identifier.");
			}
		}
	}

	return res;
}

bool PkSyntalyzer::chkWrite()
{
	bool res = false;

	if (m_line[m_nIndex++].Id == LNG_WRITE)
	{
		if (checkIndex() && m_line[m_nIndex++].Id == LNG_LBR)
		{
			if (checkIndex() && m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex++) == PkIdnTypes::Int)
			{
				if (checkIndex() && m_line[m_nIndex++].Id == LNG_RBR)
				{
					if (checkIndex() == false)
					{
						res = true;
					}
					else
					{
						addError(L"Unexpected end of line");
					}
				}
				else
				{
					addError(L"Expected \")\" keyword");
				}
			}
			else
			{
				addError(L"Missing identifier.");
			}
		}
	}

	return res;
}

bool PkSyntalyzer::chkBool()
{
	//TODO: add math expression to analyze
	bool res = false;	

	if (chckMath() == true) // left expression
	{
		if (m_line[m_nIndex].Id == LNG_GR
			|| m_line[m_nIndex].Id == LNG_LS
			//|| m_line[m_nIndex].Id == LNG_ASN
			|| m_line[m_nIndex].Id == LNG_NEQ
			|| m_line[m_nIndex].Id == LNG_GREQ
			|| m_line[m_nIndex].Id == LNG_LSEQ
			|| m_line[m_nIndex].Id == LNG_EQ)  // boolean operator
		{
			m_nIndex++;
			if (chckMath() == true) // right expression
			{
				res = true;
			} // right expression
			else
			{
				res = false;
			}
		} // // boolean operator
		else
		{
			addError(L"Unexpected terminal detected.");
		}
	}
	else // left expression
	{
		res = false;
	}

	return res;
}

bool PkSyntalyzer::chkIf()
{
	bool res = false;

	if (m_line.size() < 8) // if x == y then goto l:
	{
		addError(L"Missed operator.");
		return res;
	}
	
	if (checkIndex() && m_line[m_nIndex++].Id == LNG_IF)
	{
		if (chkBool() == true)
		{
			if (checkIndex() && m_line[m_nIndex++].Id == LNG_THEN)
			{
				res = chkGoto();
			}
			else
			{
				addError(L"Expected \"then\" keyword.");
			}
		}
		else
		{
			res = false;
		}
	}

	return res;
}

bool PkSyntalyzer::chkFor()
{
	bool res = false;

	if (m_line[m_nIndex++].Id == LNG_FOR)
	{
		if (chkAssign() == true)
		{
			//m_nIndex++;
			if (checkIndex() && m_line[m_nIndex++].Id == LNG_BY)
			{
				if (chkAssign() == true)
				{
					//m_nIndex++;
					if (checkIndex() && m_line[m_nIndex].Id == LNG_WHILE)
					{
						m_nIndex++;
						if (chkBool() == true)
						{
							//m_nIndex++;
							if (checkIndex() && m_line[m_nIndex++].Id == LNG_DO)
							{
								res = chkAssign();
							}
							else
							{
								addError(L"Expected \"do\" keyword.");
							}
						}
						else
						{
							res = false;
						}
					}
					else
					{
						addError(L"Expected \"while\" keyword.");
					}
				}
				else
				{
					res = false;
				}
			}
			else
			{
				addError(L"Missing \"by\" keyword.");
			}
		}
		else
		{
			res = false;
		}
	}

	return res;
}

bool PkSyntalyzer::chkGoto()
{
	bool res = false;

	if (checkIndex() && m_line[m_nIndex++].Id == LNG_GOTO)
	{
		if (checkIndex() && m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex++) == PkIdnTypes::Lbl)
		{
			if (checkIndex() && m_line[m_nIndex].Id == LNG_CLN)
			{
				res = true;
			}
			else
			{
				addError(L"Missed \":\".");
			}
		}
		else
		{
			addError(L"Missed label.");
		}
	}
	else
	{
		addError(L"Missed \"goto\" operator.");
	}

	return res;
}

bool PkSyntalyzer::chkExpr()
{
	bool res = false;

	if (m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex) == PkIdnTypes::Lbl)
	{
		res = chkLabel();
	}
	else
	{
		res = chkAssign();
	}

	return res;
}

bool PkSyntalyzer::chkLabel()
{
	bool res = false;

	if (m_line[0].Class == PkLexemClasses::IDN && getIdnType(0) == PkIdnTypes::Lbl)
	{
		m_nIndex = 1;
		if (checkIndex() && m_line[1].Id == LNG_CLN)
			res = true;
		else 
			addError(L"Missed \":\".");
	}
	else
	{
		addError(L"Missing label identifier.");
	}

	return res;
}

bool PkSyntalyzer::chkAssign()
{
	bool res = false;

	if (checkIndex() && m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex++) == PkIdnTypes::Int)
	{
		if (checkIndex() && m_line[m_nIndex++].Id == LNG_ASN)
		{
			res = chckMath();
		}
		else
		{
			addError(L"Expected \"\"\" keyword.");
		}
	}
	else
	{
		addError(L"Missing identifier.");
	}

	return res;
}

bool PkSyntalyzer::chckMath(bool reset)
{
	static size_t brackets = 0;
	if (reset)
		brackets = 0;

	bool res = false;

	if (m_line[m_nIndex].Id == LNG_LBR)
	{
		brackets++;
		m_nIndex++;
		if (checkIndex() == false)
			addError(L"Missing \")\".");
		else
			res = chckMath(false);
	}
	else if (m_line[m_nIndex].Id == LNG_RBR)
	{
		brackets--;
		m_nIndex++;
		if (checkIndex() == false)
			if (brackets != 0)
				addError(L"Unexpected \")\".");
			else
				res = true;
		else
			res = chckMath(false);
	}
	else if (m_line[m_nIndex].Id == LNG_MINUS)
	{
		if (m_line[++m_nIndex].Class == PkLexemClasses::CON 
			|| (m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex) == PkIdnTypes::Int))
		{
			if (m_nIndex + 1 >= m_line.size())
			{
				res = true;
			}
			else
			{
				res = chckMath(false);
			}			
		}
		else
		{
			addError(L"Unexpected unary minus.");
		}
	}
	else if (m_line[m_nIndex].Class == PkLexemClasses::CON 
		|| (m_line[m_nIndex].Class == PkLexemClasses::IDN && getIdnType(m_nIndex) == PkIdnTypes::Int))
	{
		m_nIndex++;

		if (checkIndex() == false) // end of line
		{
			res = true;
		}
		else
		{
			if (m_line[m_nIndex].Id == LNG_PLUS
				|| m_line[m_nIndex].Id == LNG_MINUS
				|| m_line[m_nIndex].Id == LNG_MULT
				|| m_line[m_nIndex].Id == LNG_DIV
				|| m_line[m_nIndex].Id == LNG_SQR)
			{
				m_nIndex++;
				if (checkIndex() == true)
				{
					res = chckMath(false);
				}
				else
				{
					addError(L"Unexpected keyword " + m_line[m_nIndex-1].Name + L".");
				}
			}
			else if (m_line[m_nIndex].Id == LNG_GR
				|| m_line[m_nIndex].Id == LNG_LS
				|| m_line[m_nIndex].Id == LNG_NEQ
				|| m_line[m_nIndex].Id == LNG_GREQ
				|| m_line[m_nIndex].Id == LNG_LSEQ
				|| m_line[m_nIndex].Id == LNG_EQ
				|| m_line[m_nIndex].Id == LNG_BY
				|| m_line[m_nIndex].Id == LNG_THEN
				|| m_line[m_nIndex].Id == LNG_WHILE
				|| m_line[m_nIndex].Id == LNG_DO)    // start boolean operator
			{
				res = true;
			}
			else if (m_line[m_nIndex].Id == LNG_LBR)
			{
				res = chckMath(false);
			}
			else if (m_line[m_nIndex].Id == LNG_RBR)
			{ 
				m_nIndex++;
				brackets--;

				if (checkIndex()
					&& (m_line[m_nIndex].Id == LNG_GR
					|| m_line[m_nIndex].Id == LNG_LS
					|| m_line[m_nIndex].Id == LNG_NEQ
					|| m_line[m_nIndex].Id == LNG_GREQ
					|| m_line[m_nIndex].Id == LNG_LSEQ
					|| m_line[m_nIndex].Id == LNG_EQ
					|| m_line[m_nIndex].Id == LNG_BY
					|| m_line[m_nIndex].Id == LNG_THEN
					|| m_line[m_nIndex].Id == LNG_WHILE
					|| m_line[m_nIndex].Id == LNG_DO))
				{
					m_nIndex++;
					if (checkIndex())
						res = chckMath(false);
					else
						addError(L"ololo");
				}
				else
				{
					res = true;
				}
			}
			else
			{
				addError(L"Unexpected keyword " + m_line[m_nIndex].Name + L".");
			}
		}
	}
	else
	{
		addError(L"Unexpected keyword " + m_line[m_nIndex].Name + L".");
	}

	if (res && reset && brackets != 0)
	{
		res = false;
		addError(L"Brackets error");
	}

	return res;
}

void PkSyntalyzer::addError(const std::wstring& msg, const std::wstring& msg1)
{
	std::wstring errMsg = L"line ";
	errMsg += std::to_wstring(m_nLine);
	errMsg += L". ";
	errMsg += msg;
	if (msg1.empty() == false)
		errMsg += L" " + msg1;

	m_errors[m_nLine].push_back(errMsg);
}

PkLang::PkIdnTypes PkSyntalyzer::getIdnType(const size_t index) const
{
	PkLang::PkIdnTypes res = PkLang::PkIdnTypes::Undef;

	const auto& idn = std::find(m_idents.begin(), m_idents.end(), m_line[index].Index);
	if (idn != m_idents.end())
		res = idn->Type;

	return res;
}