#pragma once

#include "../PkLangDefs/PkLang.h"
#include <vector>
#include <stack>
#include <string>

class Builder
{
public:
	Builder(const PkLang::TmPkOutLexems& lexems);
	~Builder();

public:
	bool Build();
	const PkLang::TvPkOutLexems GetPoliz() const { return m_poliz; }

private:
	const size_t getPriority(const PkLang::PkOutLexema& lexem) const;

private:
	PkLang::TmPkOutLexems m_lexems;

	PkLang::TvPkOutLexems m_poliz;
	std::stack<PkLang::PkOutLexema> m_stack;
};

