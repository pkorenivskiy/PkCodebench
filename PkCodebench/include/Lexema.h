#pragma once

#include <string>

enum LexemClasses
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

struct PkLexema
{
public:	
	std::wstring Name;
	LexemClasses Class;
	size_t Id;
};
