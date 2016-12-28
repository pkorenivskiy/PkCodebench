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

enum IdnTypes
{
	Integer
};

struct PkLexema
{
public:	
	std::wstring Name;
	LexemClasses Class;
	size_t Id;
};

struct PkOutLexema
{
	size_t Line;
	std::wstring Name;
	size_t Id;
	LexemClasses Class;
	size_t Index;
};

struct PkOutIdn
{
	size_t Index;
	std::wstring Name;
	IdnTypes Type;
};

struct PkOutConst
{
	size_t Index;
	int Value;
};