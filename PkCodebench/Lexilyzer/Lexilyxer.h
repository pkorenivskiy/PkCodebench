#pragma once

#include "cbtypes.h"
#include "PkLangDefs.h"


class CLexilyxer
{
public:
	CLexilyxer();
	~CLexilyxer();

protected:
	typedef std::map<std::wstring, PkLexema> mapLexems;

public:
	bool Analyze(const TvLnLexems& lexems);

private:
	void initLexems();

private:
	bool isTerm(const std::wstring& lex);
	bool isIdn(const std::wstring& lex);
	bool isCon(const std::wstring& lex);
	bool isKw(const std::wstring& lex);


	void processDeclare(const std::vector<PkLexema>& lexems, const size_t line);

private:
	mapLexems m_mLexems;

	TvOutLexems m_vOutLex;
	TmOutIdent m_mOutIdn;
	TvOutConst m_vOutConst;

	std::map<size_t, std::wstring> m_mErrors;

private:
	const std::wstring LOGICALSYM;
	const std::wstring OPERATORS;
};

