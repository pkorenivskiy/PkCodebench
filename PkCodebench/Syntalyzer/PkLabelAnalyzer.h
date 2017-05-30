#pragma once
#include "PkBaseAnalyzer.h"
class PkLabelAnalyzer final : public PkBaseAnalyzer 
{
public:
	PkLabelAnalyzer();
	~PkLabelAnalyzer();

	virtual bool Analyze(PkLang::TvPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors) override final;
};

