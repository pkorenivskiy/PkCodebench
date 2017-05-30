#include "stdafx.h"
#include "PkBaseAnalyzer.h"


void PkBaseAnalyzer::addError(PkLang::TmErrors& errors, const std::wstring& msg, size_t line, const std::wstring& msg1)
{
	std::wstring errMsg = L"line ";
	errMsg += std::to_wstring(line);
	errMsg += L". ";
	errMsg += msg;
	if (msg1.empty() == false)
		errMsg += L" " + msg1;

	errors[line].push_back(errMsg);
}

PkLang::PkIdnTypes PkBaseAnalyzer::getIdnType(const PkLang::TvPkOutIdnts& idents, const size_t index)
{
	PkLang::PkIdnTypes res = PkLang::PkIdnTypes::Undef;

	const auto& idn = std::find(idents.begin(), idents.end(), index);
	if (idn == idents.end())
		res = idn->Type;

	return res;
}