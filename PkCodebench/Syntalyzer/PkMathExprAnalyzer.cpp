#include "stdafx.h"
#include "PkMathExprAnalyzer.h"


PkMathExprAnalyzer::PkMathExprAnalyzer()
{
}


PkMathExprAnalyzer::~PkMathExprAnalyzer()
{
}

bool PkMathExprAnalyzer::Analyze(PkLang::TvPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors)
{
	bool bRes = false;

	//size_t nLine = lexems.begin()->Line;	

	//if (m_nIndex >= lexems.size())
	//	return false;

	////for (auto& itLex = lexems.begin() + m_nIndex; itLex != lexems.end(); itLex++)
	//for (m_nIndex; m_nIndex < lexems.size(); ++m_nIndex)
	//{
	//	auto& itLex = lexems[m_nIndex];
	//	if (itLex.Id == LNG_LBR) // (
	//	{
	//		m_nIndex++;
	//		if (Analyze(lexems, idents, consts, errors) == false || m_nIndex >= lexems.size() || lexems[++m_nIndex].Id == LNG_RBR)
	//		{
	//			return false;
	//		}			
	//	}
	//	else if (itLex.Id == LNG_MINUS)
	//	{
	//		itLex = lexems[m_nIndex];
	//		if (itLex == lexems.end() || itLex->Class != PkLang::PkLexemClasses::CON)
	//		{
	//			addError(errors, L"constant expected ", nLine);
	//		}
	//	}
	//	else if (itLex->Class == PkLang::PkLexemClasses::IDN)
	//	{
	//		m_nIndex = itLex->Index + 1;

	//	}
	//}

	return bRes;
}
