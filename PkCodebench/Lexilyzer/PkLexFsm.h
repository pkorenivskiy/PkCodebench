#pragma once

#include <string.h>
#include <memory>

#include "PkLexFsmState.h"
#include "PkLexFsmEvent.h"
#include "../PkFSM/PkFiniteStateMachine.h"
#include "../PkLogger/PkLogConsole.h"
#include "../PkLangDefs/PkLang.h"


namespace PkLex
{
	class PkLexFsm : public PkFSM::PkFiniteStateMachine<PkLexFsmStates, PkLexFsmEvents>
	{
	public:
		PkLexFsm(const std::wstring& text)
			: PkFiniteStateMachine<PkLexFsmStates, PkLexFsmEvents>(START)
			, m_sText(text)			
		{
			LOG("Lexilyser init.");
			AddState(TRM);
			AddState(IDN);			
			AddState(CON);
			AddState(LEX);
			AddState(ERR);
			AddState(NLN);

			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::CH,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::DG,		PkLexFsmStates::CON);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::IDN,		PkLexFsmEvents::CH,		PkLexFsmStates::IDN);
			AddTransition(PkLexFsmStates::IDN,		PkLexFsmEvents::DG,		PkLexFsmStates::IDN);
			AddTransition(PkLexFsmStates::IDN,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::IDN,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::CH,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::DG,		PkLexFsmStates::CON);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::CH,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::DG,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);
		}

	public:
		bool Process(PkLang::TmPkOutLexems& lexems, PkLang::TmPkOutConsts& consts, PkLang::TmPkOutIdns& idents, PkLang::TmErrors& errors)
		{
			size_t nLine = 1;
			std::wstring lexema(L"");
			for (auto& itCh = m_sText.begin(); itCh != m_sText.end(); ++itCh)
			{
				AcceptEvent(PkLexFsmEvent(*itCh));
				if (GetCurrentState() == PkLexFsmStates::START)
				{
					//if (lexema.find_first_of(L'\r') != std::wstring::npos 
					//	|| lexema.find_first_of(L'\n') != std::wstring::npos) // new line lexema
					if (GetPreviosState() == PkLexFsmStates::NLN)
					{
						nLine++;
						lexema.erase();
					}
					else
					{
						LOG(std::string(lexema.begin(), lexema.end()));
						
						PkLang::PkOutLexema outLex;
						outLex.Name = lexema;

						lexems[nLine].push_back(outLex);

						lexema.erase();
					}					
				}
				else if (GetCurrentState() == PkLexFsmStates::ERR)
				{
					errors[nLine].push_back(L"Error.");					
					Reset(PkLexFsmStates::START);
					while (std::iswspace(*(++itCh)));
				}
				else
				{
					lexema += *itCh;
				}
			}

			if (lexema.empty() == false)
			{
				LOG(std::string(lexema.begin(), lexema.end()));

				PkLang::PkOutLexema outLex;
				outLex.Name = lexema;

				lexems[nLine].push_back(outLex);
			}

			return true;
		}

	private:		
		std::wstring m_sText;
	};

}
