#pragma once

#include "PkBaseAnalyzer.h"
#include "../PkLangDefs/PkLang.h"

class PkDeclAnalyzer final : public PkBaseAnalyzer
{
public:
	virtual bool Analyze(PkLang::TvPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors) override final;
};
