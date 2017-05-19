#pragma once

#include "../PkLangDefs/PkLang.h"

class PkBaseAnalyzer abstract
{
public:
	PkBaseAnalyzer();
	virtual ~PkBaseAnalyzer();

public:
	virtual bool Analyze(PkLang::TvPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors) = 0;
};

