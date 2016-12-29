#pragma once

#include <vector>
#include <string>
#include <map>

#include "Lexema.h"

typedef std::vector<std::wstring> TvErrors;
typedef std::map<size_t, std::vector<std::wstring>> TmErrors;
typedef TmErrors::value_type TmErrorsVt;

typedef std::vector<PkLexema> TvLexLine;
typedef TvLexLine::iterator TvLexLineIt;
typedef std::vector<TvLexLine> TvLexLines; // line -> lexems
typedef TvLexLines::iterator TvLexLinesIt;

typedef std::vector<PkOutLexema> TvOutLexems;
typedef std::map<std::wstring, PkOutIdn> TmOutIdent;
typedef std::vector<PkOutConst> TvOutConst;


