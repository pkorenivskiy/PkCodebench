#pragma once

#include <vector>
#include "Lexema.h"

static const std::vector<CPkLexema> LEXEMS =
{
	{ CPkLexema{ L"int", Keyword, 1 } },
	{ CPkLexema{ L"label", Keyword, 2 } },
				 
	{ CPkLexema{ L"for", Keyword, 3 } },
	{ CPkLexema{ L"by", Keyword, 4 } },
	{ CPkLexema{ L"while", Keyword, 5 } },
	{ CPkLexema{ L"end", Keyword, 6 } },
				 
	{ CPkLexema{ L"if", Keyword, 7 } },
	{ CPkLexema{ L"then", Keyword, 8 } },
	{ CPkLexema{ L"goto", Keyword, 9 } },
				 
	{ CPkLexema{ L"read", Keyword, 10 } },
	{ CPkLexema{ L"write", Keyword, 11 } },
				 
	{ CPkLexema{ L"+", Operator, 12 } },
	{ CPkLexema{ L"-", Operator, 13 } },
	{ CPkLexema{ L"*", Operator, 14 } },
	{ CPkLexema{ L"/", Operator, 15 } },
	{ CPkLexema{ L"^", Operator, 16 } },
				 
	{ CPkLexema{ L"-", Operator, 17 } }, //unary minus
				 
	{ CPkLexema{ L"(", Delimiter, 18 } },
	{ CPkLexema{ L")", Delimiter, 19 } },
				 
	{ CPkLexema{ L">", Operator, 20 } },
	{ CPkLexema{ L"<", Operator, 21 } },
	{ CPkLexema{ L"=", Operator, 22 } },
	{ CPkLexema{ L"!=", Operator, 23 } },
	{ CPkLexema{ L">=", Operator, 24 } },
	{ CPkLexema{ L"<=", Operator, 25 } },
	{ CPkLexema{ L"!", Operator, 26 } },
				 
	/*{ CPkLexema{ L"begin", Keyword, 27 } },
	{ CPkLexema{ L"begin", Keyword, 28 } },
	{ CPkLexema{ L"begin", Keyword, 29 } },
	{ CPkLexema{ L"begin", Keyword, 30 } }*/
};
