#pragma once

#include "../PkLangDefs/PkLang.h"

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
	virtual void addError(PkLang::TmErrors& errors, const std::wstring& msg, size_t line, const std::wstring& msg1 = L"");
	PkLang::PkIdnTypes getIdnType(const PkLang::TvPkOutIdnts& idents, const size_t index);
protected:
	size_t m_nIndex;
};

