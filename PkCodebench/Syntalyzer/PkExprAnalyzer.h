#pragma once

#include "PkBaseAnalyzer.h"

class PkExprAnalyzer : public PkBaseAnalyzer
{
public:
	PkExprAnalyzer()
		: PkBaseAnalyzer(0)
	{}
	PkExprAnalyzer(size_t nIndex)
		: PkBaseAnalyzer(nIndex)
	{}
	virtual ~PkExprAnalyzer() { }

public:
	// Inherited via PkBaseAnalyzer
	virtual bool Analyze(PkLang::TvPkOutLexems & lexems, PkLang::TvPkOutIdnts & idents, PkLang::TmPkOutConsts & consts, PkLang::TmErrors & errors) override;
};

