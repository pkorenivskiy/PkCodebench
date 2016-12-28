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

protected:
	enum ForStates
	{
		Init = 1,
		Expr,
		By,
		LExpr,
		Do
	};

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

	size_t validate(const std::vector<PkLexema>& lnLexems, size_t line, size_t start = 0);

	bool isVarNameValid(const std::wstring& st);

	void processDeclare(const std::vector<PkLexema>& lexems, const size_t line, size_t start = 0);
	void processRead(const std::vector<PkLexema>& lexems, const size_t line, size_t start = 0);
	void processWrite(const std::vector<PkLexema>& lexems, const size_t line, size_t start = 0);
	void processFor(const std::vector<PkLexema>& lexems, const size_t line, size_t start = 0);

	size_t processExpr(const std::vector<PkLexema>& lexems, const size_t line, size_t start = 0);

private:
	void clearResult();
	void addError(size_t nLine, const std::wstring& stoken, const std::wstring& msg);
	
private:
	TvLnLexems m_vInLexems;
	size_t m_nLine;

private:
	TvOutLexems m_vOutLex;
	TmOutIdent m_mOutIdn;
	TvOutConst m_vOutConst;

	TmErrors m_mErrors;

private:
	mapLexems m_mLexems;

private:
	const std::wstring LOGICALSYM;
	const std::wstring OPERATORS;
};

