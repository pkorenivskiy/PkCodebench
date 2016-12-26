#pragma once

#include "cbtypes.h"
#include "PkLangDefs.h"


class CLexilyzer
{
public:
	CLexilyzer();
	~CLexilyzer();

protected:
	typedef std::map<std::wstring, PkLexema> mapLexems;

public:
	bool Analyze(const TvLnLexems& lexems);
	const TvOutLexems GetLexems() const { return m_vOutLex; }
	const TmOutIdent GetIdns() const { return m_mOutIdn; }
	const TvOutConst GetConst() const { return m_vOutConst; }
	const TmErrors GetErrors() const { return m_mErrors; }

private:
	void initLexems();

private:
	bool isTerm(const std::wstring& lex);
	bool isIdn(const std::wstring& lex);
	bool isCon(const std::wstring& lex);
	bool isKw(const std::wstring& lex);

	bool isVarNameValid(const std::wstring& st);

	void processDeclare(const std::vector<PkLexema>& lexems, const size_t line);
	void processRead(const std::vector<PkLexema>& lexems, const size_t line);
	void processWrite(const std::vector<PkLexema>& lexems, const size_t line);

	void addError(size_t nLine, const std::wstring& stoken, const std::wstring& msg);
private:
	mapLexems m_mLexems;

	TvOutLexems m_vOutLex;
	TmOutIdent m_mOutIdn;
	TvOutConst m_vOutConst;

	TmErrors m_mErrors;

private:
	const std::wstring LOGICALSYM;
	const std::wstring OPERATORS;
};

