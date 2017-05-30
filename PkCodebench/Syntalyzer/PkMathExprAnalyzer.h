#pragma once

#include "PkBaseAnalyzer.h"

class PkMathExprAnalyzer final : public PkBaseAnalyzer
{
public:
	PkMathExprAnalyzer();
	PkMathExprAnalyzer(const size_t index)
		: PkBaseAnalyzer(index) {}
	~PkMathExprAnalyzer();

public:
	virtual bool Analyze(PkLang::TvPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors) override final;

private:
	
};

