#pragma once

#include <string>
#include <map>

#define POPR std::pair<std::wstring, size_t>

static const std::map<std::wstring, size_t> PRIORITY =
{
	POPR(L"while", 0),
	POPR(L"do", 1),
	POPR(L"end", 1),
	POPR(L",", 1),
	POPR(L"if", 1),
	POPR(L"(", 1),
	POPR(L"then",2),
	POPR(L"else", 2),
	POPR(L")", 2),
	POPR(L"=", 4),
	POPR(L"<", 8),
	POPR(L">", 8),
	POPR(L">=", 8),
	POPR(L"<=", 8),
	POPR(L"==", 8),
	POPR(L"!=", 8),
	POPR(L"+", 9),
	POPR(L"-", 9),
	POPR(L"*", 10),
	POPR(L"/", 10),
	POPR(L"@", 10),
	POPR(L"^", 11)
};
