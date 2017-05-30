#pragma once

#include "../PkLangDefs/PkLang.h"

class PkSyntalyzer
{
public:
	PkSyntalyzer(const PkLang::TmPkOutLexems& lexems, const PkLang::TvPkOutIdnts& idents, const PkLang::TmPkOutConsts& consts);
	~PkSyntalyzer();

public:
	bool Analyze();
	const size_t ErrorCount() const { return m_errors.size(); }
	const PkLang::TmErrors Errors() const { return m_errors; }
	const PkLang::TvPkOutIdnts GetIdents() const { return m_idents; }

private:
	bool chkDecl();
	bool chkListIDN();
	bool chkRead();
	bool chkWrite();
	bool chkBool();
	bool chkIf();
	bool chkFor();
	bool chkGoto();
	bool chkExpr();
	bool chkLabel();
	bool chkAssign();
	
	/*
	*  recursive
	*  expression must be start IDN
	*  check while TRM or end line detected
	*/
	bool chckMath(bool reset = true);

private:
	void addError(const std::wstring& msg, const std::wstring& msg1 = L"");
	PkLang::PkIdnTypes getIdnType(const size_t index) const;
	const bool checkIndex() const { return m_nIndex < m_line.size(); }

private:
	size_t m_nIndex;
	size_t m_nLine;
	PkLang::TmPkOutLexems m_lexems;
	PkLang::TvPkOutLexems m_line;
	PkLang::TvPkOutIdnts m_idents;
	PkLang::TmPkOutConsts m_consts;
	PkLang::TmErrors m_errors;
};


