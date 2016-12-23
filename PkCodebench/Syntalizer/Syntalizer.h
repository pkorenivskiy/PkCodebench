#pragma once

#include <functional>

#include "cbtypes.h"
#include "States.h"

#ifdef SYNTALIZER_EXPORTS
	#define SYNTALIZER_API __declspec(dllexport)
	//#define EXPIMP_TEMPLATE
#else
	#define SYNTALIZER_API __declspec(dllimport)
#endif // SYNTALIZER_EXPORT


class SYNTALIZER_API CSyntalizer
{
public:
	CSyntalizer();
	~CSyntalizer();

	CSyntalizer(const std::wstring& sText);

protected:
	typedef std::function<void(void)> action;	
	typedef std::map<SynStates, action> mapActions;

	typedef std::map<std::wstring, CPkLexema> mapLexems;

public:

	const TvErrors GetErrors() const;
	const std::wstring GetErrorText() const;

private:
	void initLexems();
	void initSfm();

private:
	std::wstring m_sText;
	size_t m_nPos;


private:
	mapLexems m_mLexems;
	mapActions m_actions;

	TvErrors m_Errors;
	TvLnLexems m_outLexems;

	SynStates m_curState;
	std::wstring m_curLexema;

	// SFM functions
private:
	void processChar();
	void readyLexema();
	void processLexema();

private:
	const std::wstring LOGICALSYM;
};

