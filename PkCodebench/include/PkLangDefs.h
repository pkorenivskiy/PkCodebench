#pragma once

#include <vector>
#include "Lexema.h"

static const std::vector<PkLexema> LEXEMS =
{
	{ PkLexema{ L"int", Keyword, 1 } },
	{ PkLexema{ L"label", Keyword, 2 } },
				 
	{ PkLexema{ L"for", Keyword, 3 } },
	{ PkLexema{ L"by", Keyword, 4 } },
	{ PkLexema{ L"while", Keyword, 5 } },
	{ PkLexema{ L"do", Keyword, 6 } },
				 
	{ PkLexema{ L"if", Keyword, 7 } },
	{ PkLexema{ L"then", Keyword, 8 } },
	{ PkLexema{ L"goto", Keyword, 9 } },
				 
	{ PkLexema{ L"read", Keyword, 10 } },
	{ PkLexema{ L"write", Keyword, 11 } },
				 
	{ PkLexema{ L"+", Operator, 12 } },
	{ PkLexema{ L"-", Operator, 13 } },
	{ PkLexema{ L"*", Operator, 14 } },
	{ PkLexema{ L"/", Operator, 15 } },
	{ PkLexema{ L"^", Operator, 16 } },
				 
	{ PkLexema{ L"-", Operator, 17 } }, //unary minus
				 
	{ PkLexema{ L"(", Delimiter, 18 } },
	{ PkLexema{ L")", Delimiter, 19 } },
				 
	{ PkLexema{ L">", Operator, 20 } },
	{ PkLexema{ L"<", Operator, 21 } },
	{ PkLexema{ L"=", Operator, 22 } },
	{ PkLexema{ L"!=", Operator, 23 } },
	{ PkLexema{ L">=", Operator, 24 } },
	{ PkLexema{ L"<=", Operator, 25 } },
	{ PkLexema{ L"!", Operator, 26 } },
				 
	{ PkLexema{ L":", Keyword, 27 } },
	{ PkLexema{ L",", Keyword, 28 } },
	/*{ CPkLexema{ L"begin", Keyword, 29 } },
	{ CPkLexema{ L"begin", Keyword, 30 } }*/
};
