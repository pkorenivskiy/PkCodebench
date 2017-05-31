#pragma once

#include <string>
#include <map>

#define POPR std::pair<std::wstring, size_t>

static const std::map<std::wstring, size_t> PRIORITY =
{
	POPR(L"int", -1),
	POPR(L"label", -1),
	
	POPR(L"for", 0),
	POPR(L"by", 0),
	POPR(L"while", 10),
	POPR(L"do", 10),
	
	POPR(L"if", 0),
	POPR(L"then", 10),
	POPR(L"goto", 0),
	
	POPR(L"read", 0),
	POPR(L"write", 0),
	
	POPR(L"+", 70),
	POPR(L"-", 70),
	POPR(L"*", 80),
	POPR(L"/", 80),
	POPR(L"^", 90),
		
	POPR(L"(", 0),
	POPR(L")", 10),
	
	POPR(L">", 60),
	POPR(L"<", 60),
	
	POPR(L"=", 50),
	
	POPR(L"!=", 60),
	POPR(L">=", 60),
	POPR(L"<=", 60),
	POPR(L"==", 60),
	
	POPR(L":", -1),
	POPR(L",", -1),

	POPR(L"@", 100)
};
