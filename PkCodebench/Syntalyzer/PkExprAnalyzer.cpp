#include "stdafx.h"
#include <memory>
#include "PkExprAnalyzer.h"


bool PkExprAnalyzer::Analyze(PkLang::TvPkOutLexems & lexems, PkLang::TvPkOutIdnts & idents, PkLang::TmPkOutConsts & consts, PkLang::TmErrors & errors)
{
	for (size_t i = m_nIndex; i < lexems.size(); ++i)
	{
		std::shared_ptr<PkBaseAnalyzer> analyzer(nullptr);
		if (lexems[i].Name == L"(")
		{
			analyzer = std::shared_ptr<PkBaseAnalyzer>(new PkExprAnalyzer(i, SynStates::LfBr));
		}
		else if (lexems[i].Name == L")")
		{
			if (m_nInState == SynStates::LfBr)
				return true;
			else
				return false;
		}
		else 
		{
			;
		}

		analyzer->Analyze(lexems, idents, consts, errors);
	}

	return false;
}
