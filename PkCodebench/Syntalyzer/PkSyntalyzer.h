#pragma once

#include "../PkLangDefs/PkLang.h"

class PkSyntalyzer
{
public:
	PkSyntalyzer();
	~PkSyntalyzer();

public:
	bool Analyze(PkLang::TmPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors);

private:	
};

