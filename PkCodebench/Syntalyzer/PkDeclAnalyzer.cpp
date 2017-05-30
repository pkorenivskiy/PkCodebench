#include "stdafx.h"
#include <algorithm>
#include "PkDeclAnalyzer.h"

using namespace PkLang;

bool PkDeclAnalyzer::Analyze(TvPkOutLexems& lexems, TvPkOutIdnts& idents, TmPkOutConsts& consts, TmErrors& errors)
{
	bool res = false;

	size_t nLine = lexems.begin()->Line;

	if (lexems.size() < 2)
	{
		addError(errors, L"Missed identifiers.", nLine);
		return res;
	}

	PkIdnTypes identType = PkIdnTypes::Int;
	if (lexems[0].Id == LNG_INT)
		identType = PkIdnTypes::Int;
	else if (lexems[0].Id == LNG_LABEL)
		identType = PkIdnTypes::Lbl;
	else
	{
		addError(errors, L"Syntax error.", nLine);
		return res;
	}

	auto expClass = PkLexemClasses::IDN;

	for (auto& ident = lexems.begin() + m_nIndex + 1; ident != lexems.end(); ident++)
	{
		if (ident->Class != expClass)
		{
			addError(errors, L"Syntax error.", nLine);
			return res;
		}
		
		if (expClass == PkLexemClasses::IDN)
		{
			if (ident->Class == PkLexemClasses::IDN)
			{
				auto& itId = std::find(idents.begin(), idents.end(), ident->Index);

				if (itId != idents.end())
					itId->Type = identType;
				else
					addError(errors, L"Unknown identifier.", nLine);
			}
			else
			{
				addError(errors, L"Identifier expected.", nLine);
				return res;
			}
		}
		else
		{
			if (ident->Id != LNG_CMA)
			{
				addError(errors, L"Comma expected.", nLine);
				return res;
			}
		}

		expClass = expClass == PkLexemClasses::IDN ? PkLexemClasses::TRM : PkLexemClasses::IDN;
	}

	res = true;

	return res;
}