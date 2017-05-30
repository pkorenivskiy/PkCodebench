#include "stdafx.h"
#include <memory>
#include <algorithm>
#include "PkExprAnalyzer.h"
#include "PkMathExprAnalyzer.h"


bool PkExprAnalyzer::Analyze(PkLang::TvPkOutLexems & lexems, PkLang::TvPkOutIdnts & idents, PkLang::TmPkOutConsts & consts, PkLang::TmErrors & errors)
{
	bool bRes = false;

	size_t nLine = lexems[0].Line;

	if (lexems[0].Class == PkLang::PkLexemClasses::IDN)
	{
		auto idnType = getIdnType(idents, lexems[0].Index);

		if (idnType == PkLang::PkIdnTypes::Lbl)
		{
			if (lexems.size() == 2)
			{
				if (lexems[1].Id == LNG_CLN)
					bRes = true;
				else
					addError(errors, L"Analyze error ", nLine);
			}
			else
			{
				addError(errors, L"Analyze error. Label expected ", nLine);
			}
		}
		else if (idnType == PkLang::PkIdnTypes::Int)
		{
			if (lexems.size() > 2 && lexems[1].Id == LNG_ASN)
			{
				PkMathExprAnalyzer analyzer(3);
				bRes = analyzer.Analyze(lexems, idents, consts, errors);
			}
		}
		else
		{
			addError(errors, L"Undefined identifier ", nLine);
		}
	}
	else
	{
		addError(errors, L"Analyze error. Identifier expected ", nLine);
	}


	return bRes;
}
