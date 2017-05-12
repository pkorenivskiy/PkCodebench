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
			AddState(LEX);
			AddState(CON);
			AddState(TRM);
			AddState(NLN);
			AddState(LOG);
			AddState(ERR);

			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::CH,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::DG,		PkLexFsmStates::CON);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::LG,		PkLexFsmStates::LOG);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::MN,		PkLexFsmStates::TRM);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::EQ,		PkLexFsmStates::LOG);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::TR,		PkLexFsmStates::TRM);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::CH,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::DG,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::LG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::SC,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::NL,		PkLexFsmStates::START);

			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::CH,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::DG,		PkLexFsmStates::CON);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::LG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::NL,		PkLexFsmStates::START);

			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::LG,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::MN,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::EQ,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::TR,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::NL,		PkLexFsmStates::START);

			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::LG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::SC,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);

			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::LG,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::NL,		PkLexFsmStates::ERR);
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
					if (GetPreviosState() == PkLexFsmStates::NLN)
					{
						nLine++;
						lexema.erase();
						itCh--;
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
					itCh--;
				}
				else
				{
					lexema += *itCh;
				}
			}

			if (lexema.empty() == false && GetCurrentState() == PkLexFsmStates::START && GetPreviosState() != PkLexFsmStates::NLN)
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
