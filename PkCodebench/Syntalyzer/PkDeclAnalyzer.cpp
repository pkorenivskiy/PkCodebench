#include "stdafx.h"
#include <algorithm>
#include "PkDeclAnalyzer.h"

using namespace PkLang;

bool PkDeclAnalyzer::Analyze(TvPkOutLexems& lexems, TvPkOutIdnts& idents, TmPkOutConsts& consts, TmErrors& errors)
{
	bool res = false;

	if (lexems.size() < 2)
	{
		errors[lexems.begin()->Line].push_back(L"Missed identifiers at line " + std::to_wstring(lexems.begin()->Line));
		return res;
	}

	PkIdnTypes identType = PkIdnTypes::Undef;
	if (lexems[0].Id == 0)
		identType = PkIdnTypes::Int;
	else if (lexems[0].Id == PkIdnTypes::Lbl)
		identType = PkIdnTypes::Lbl;
	else
	{
		errors[lexems.begin()->Line].push_back(L"Syntax error at line " + std::to_wstring(lexems.begin()->Line));
		return res;
	}

	for (auto& ident = lexems.begin() + 1; ident != lexems.end(); ident++)
	{
		if (ident->Class != PkLexemClasses::Variable)
		{
			errors[lexems.begin()->Line].push_back(L"Syntax error at line " + std::to_wstring(lexems.begin()->Line));
			return res;
		}
		
		auto& itId = std::find(idents.begin(), idents.end(), ident->Index);

		if (itId != idents.end())
			itId->Type = identType;
	}

	res = true;

	return res;
}