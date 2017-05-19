#include "stdafx.h"
#include "PkSyntalyzer.h"

#include <memory>
#include <string>

#include "PkBaseAnalyzer.h"
#include "PkDeclAnalyzer.h"

PkSyntalyzer::PkSyntalyzer()
{
}


PkSyntalyzer::~PkSyntalyzer()
{
}

bool PkSyntalyzer::Analyze(PkLang::TmPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors)
{
	bool res = false;

	std::shared_ptr<PkBaseAnalyzer> analyzer;

	for (auto& line : lexems)
	{
		if (line.second.empty() == false)
		{
			if (line.second[0].Id == 0)
				analyzer = std::shared_ptr<PkBaseAnalyzer>(new PkDeclAnalyzer());



			bool synChk = analyzer->Analyze(line.second, idents, consts, errors);
			if (synChk == false)
			{
				errors[line.first].push_back(L"Syntax error at line " + std::to_wstring(line.first));
				return res;
			}
		}
	}

	res = true;

	return res;
}