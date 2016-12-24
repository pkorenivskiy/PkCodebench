#pragma once

#include <vector>
#include <string>
#include <map>

#include "Lexema.h"

typedef std::vector<std::wstring> TvErrors;

typedef std::vector<std::vector<PkLexema>> TvLnLexems; // line -> lexems

typedef std::vector<PkOutLexema> TvOutLexems;
typedef std::map<std::wstring, PkOutIdn> TmOutIdent;
typedef std::vector<PkOutConst> TvOutConst;


