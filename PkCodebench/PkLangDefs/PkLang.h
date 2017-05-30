#pragma once

#include <vector>
#include <map>
#include <string>

namespace PkLang
{	
	enum PkLexemClasses
	{
		TRM = 1,
		IDN,
		CON,

		Unknown = 999
	};

	enum PkIdnTypes
	{
		Int = 1,
		Lbl,
		Undef
	};

	struct PkLexema
	{
	public:
		std::wstring Name;
		PkLexemClasses Class;
		size_t Id;
	public:
		const bool operator == (const std::wstring& str) const
		{
			return Name == str;
		}
	};



#define LNG_INT		1
#define LNG_LABEL	2

#define LNG_FOR		3
#define LNG_BY		4
#define LNG_WHILE	5
#define LNG_DO		6

#define LNG_IF		7
#define LNG_THEN	8
#define LNG_GOTO	9

#define LNG_READ	10
#define LNG_WRITE	11

#define LNG_PLUS	12
#define LNG_MINUS	13
#define LNG_MULT	14
#define LNG_DIV		15
#define LNG_SQR		16

#define LNG_UMINUS	17

#define LNG_LBR		18
#define LNG_RBR		19

#define LNG_GR		20
#define LNG_LS		21
#define LNG_ASN		22
#define LNG_NEQ		23
#define LNG_GREQ	24
#define LNG_LSEQ	25
#define LNG_EQ		26

#define LNG_CLN		27
#define LNG_CMA		28


	static const std::vector<PkLexema> LEXEMS =
	{
		{ PkLexema{ L"int",		TRM,	LNG_INT } }, //1
		{ PkLexema{ L"label",	TRM,	LNG_LABEL } }, //2

		{ PkLexema{ L"for",		TRM,	LNG_FOR } }, //3
		{ PkLexema{ L"by",		TRM,	LNG_BY } }, //4
		{ PkLexema{ L"while",	TRM,	LNG_WHILE } }, //5
		{ PkLexema{ L"do",		TRM,	LNG_DO } }, //6

		{ PkLexema{ L"if",		TRM,	LNG_IF } }, //7
		{ PkLexema{ L"then",	TRM,	LNG_THEN } }, //8
		{ PkLexema{ L"goto",	TRM,	LNG_GOTO } }, //9

		{ PkLexema{ L"read",	TRM,	LNG_READ } }, //10
		{ PkLexema{ L"write",	TRM,	LNG_WRITE } }, //11

		{ PkLexema{ L"+",		TRM,	LNG_PLUS } },
		{ PkLexema{ L"-",		TRM,	LNG_MINUS } },
		{ PkLexema{ L"*",		TRM,	LNG_MULT } },
		{ PkLexema{ L"/",		TRM,	LNG_DIV } },
		{ PkLexema{ L"^",		TRM,	LNG_SQR } },

		{ PkLexema{ L"-",		TRM,	LNG_UMINUS } }, //unary minus

		{ PkLexema{ L"(",		TRM,	LNG_LBR } },
		{ PkLexema{ L")",		TRM,	LNG_RBR } },

		{ PkLexema{ L">",		TRM,	LNG_GR } },
		{ PkLexema{ L"<",		TRM,	LNG_LS } },
		{ PkLexema{ L"=",		TRM,	LNG_ASN } },
		{ PkLexema{ L"!=",		TRM,	LNG_NEQ } },
		{ PkLexema{ L">=",		TRM,	LNG_GREQ } },
		{ PkLexema{ L"<=",		TRM,	LNG_LSEQ } },
		{ PkLexema{ L"==",		TRM,	LNG_EQ } },

		{ PkLexema{ L":",		TRM,	LNG_CLN } },
		{ PkLexema{ L",",		TRM,	LNG_CMA } }
	};

	struct PkOutLexema
	{
		size_t Line;
		std::wstring Name;
		size_t Id;
		PkLexemClasses Class;
		size_t Index;

		const bool operator > (const PkOutLexema& x)
		{
			return Line > x.Line;
		}
	};

	typedef std::vector<PkOutLexema> TvPkOutLexems;
	typedef std::map<size_t, TvPkOutLexems> TmPkOutLexems;

	struct PkOutIdn
	{
		size_t Index;
		std::wstring Name;
		PkIdnTypes Type;

		const bool operator == (const std::wstring& str) const
		{
			return Name == str;
		}

		const bool operator == (const size_t& idx) const
		{
			return Index == idx;
		}
	};

	//typedef std::map<size_t, PkOutIdn> TmPkOutIdns;
	typedef std::vector<PkOutIdn> TvPkOutIdnts;

	struct PkOutConst
	{
		size_t Index;
		int Value;
	};

	typedef std::map<size_t, PkOutConst> TmPkOutConsts;

	typedef std::map<size_t, std::vector<std::wstring>> TmErrors;
}
