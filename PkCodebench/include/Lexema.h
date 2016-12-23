#pragma once

#include <string>

enum LexemTypes
{
	Keyword,
	Operator,
	Variable,
	Label,
	Const,
	Delimiter,
	WhiteDelimiter,

	Unresolves = 900,
	Unknown = 999
};

class CPkLexema
{
public:	
	std::wstring Name;
	LexemTypes Class;
	size_t Id;
};
