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

private:
	const size_t getPriority(const std::wstring& lexem) const;

private:
	PkLang::TmPkOutLexems m_lexems;

	std::vector<std::wstring> m_poliz;
	std::stack<std::wstring> m_stack;
};

