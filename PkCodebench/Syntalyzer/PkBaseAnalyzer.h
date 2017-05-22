#pragma once

#include "../PkLangDefs/PkLang.h"

enum class SynStates
{
	Start,
	Var,
	Const,
	LfBr,
	RgBr,

	End
};

class PkBaseAnalyzer abstract
{
public:
	PkBaseAnalyzer()
		:m_nIndex(0)
	{}
	PkBaseAnalyzer(const size_t nIndex)
		:m_nIndex(nIndex)
	{}
	virtual ~PkBaseAnalyzer() {}

public:
	virtual bool Analyze(PkLang::TvPkOutLexems& lexems, PkLang::TvPkOutIdnts& idents, PkLang::TmPkOutConsts& consts, PkLang::TmErrors& errors) = 0;

protected:
	size_t m_nIndex;
};

