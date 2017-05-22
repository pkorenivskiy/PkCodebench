#pragma once

#include "PkBaseAnalyzer.h"

class PkExprAnalyzer : public PkBaseAnalyzer
{
public:
	PkExprAnalyzer()
		: PkBaseAnalyzer(0)
		, m_nInState(SynStates::Start)
	{}
	PkExprAnalyzer(size_t nIndex, SynStates inState)
		: PkBaseAnalyzer(nIndex)
		, m_nInState(inState)
	{}
	virtual ~PkExprAnalyzer() { }

public:
	// Inherited via PkBaseAnalyzer
	virtual bool Analyze(PkLang::TvPkOutLexems & lexems, PkLang::TvPkOutIdnts & idents, PkLang::TmPkOutConsts & consts, PkLang::TmErrors & errors) override;

protected:
	SynStates m_nInState;
};

