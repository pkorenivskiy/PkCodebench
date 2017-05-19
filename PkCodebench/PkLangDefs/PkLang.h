#pragma once

#include <vector>
#include <map>
#include <string>

namespace PkLang
{
	enum PkLexemClasses
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

	enum PkIdnTypes
	{
		Int,
		Lbl
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

	static size_t LEXEMINDEX = 1;
	static const std::vector<PkLexema> LEXEMS =
	{
		{ PkLexema{ L"int",		Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"label",	Keyword,	LEXEMINDEX++ } },

		{ PkLexema{ L"for",		Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"by",		Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"while",	Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"do",		Keyword,	LEXEMINDEX++ } },

		{ PkLexema{ L"if",		Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"then",	Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"goto",	Keyword,	LEXEMINDEX++ } },

		{ PkLexema{ L"read",	Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L"write",	Keyword,	LEXEMINDEX++ } },

		{ PkLexema{ L"+",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"-",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"*",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"/",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"^",		Operator,	LEXEMINDEX++ } },

		{ PkLexema{ L"-",		Operator,	LEXEMINDEX++ } }, //unary minus

		{ PkLexema{ L"(",		Delimiter,	LEXEMINDEX++ } },
		{ PkLexema{ L")",		Delimiter,	LEXEMINDEX++ } },

		{ PkLexema{ L">",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"<",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"=",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"!=",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L">=",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"<=",		Operator,	LEXEMINDEX++ } },
		{ PkLexema{ L"==",		Operator,	LEXEMINDEX++ } },

		{ PkLexema{ L":",		Keyword,	LEXEMINDEX++ } },
		{ PkLexema{ L",",		Keyword,	LEXEMINDEX++ } }
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
	};

	//typedef std::map<size_t, PkOutIdn> TmPkOutIdns;
	typedef std::vector<PkOutIdn> TvPkOutIdtns;

	struct PkOutConst
	{
		size_t Index;
		int Value;
	};

	typedef std::map<size_t, PkOutConst> TmPkOutConsts;

	typedef std::map<size_t, std::vector<std::wstring>> TmErrors;
}
