#pragma once

#include <string.h>
#include <memory>
#include <algorithm>

#include <locale>
#include <codecvt>

#include "PkLexFsmState.h"
#include "PkLexFsmEvent.h"
#include "../PkFSM/PkFiniteStateMachine.h"
#include "../PkLogger/PkLogConsole.h"
#include "../PkLangDefs/PkLang.h"


namespace PkLex
{
	class PkLexFsm : public PkFSM::PkFiniteStateMachine<PkLexFsmState, PkLexFsmEvent, PkFSM::PkOnMoveFunctor<PkLexFsmState, PkLexFsmEvent>>
	{
	public:
		PkLexFsm(const std::wstring& text)
			: PkFiniteStateMachine<PkLexFsmState, PkLexFsmEvent, PkFSM::PkOnMoveFunctor<PkLexFsmState, PkLexFsmEvent>>(PkLexFsmStates::START)
			, m_sText(text)			
		{
			LOG("Lexilyzer init.");
			AddState(PkLexFsmStates::LEX);
			AddState(PkLexFsmStates::CON);
			AddState(PkLexFsmStates::TRM);
			AddState(PkLexFsmStates::NLN);
			AddState(PkLexFsmStates::LOG);
			AddState(PkLexFsmStates::LOG2);
			AddState(PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::CH,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::DG,		PkLexFsmStates::CON);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::LG,		PkLexFsmStates::LOG);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::MN,		PkLexFsmStates::TRM);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::EQ,		PkLexFsmStates::LOG);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::TR,		PkLexFsmStates::TRM);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::NL,		PkLexFsmStates::NLN);
			AddTransition(PkLexFsmStates::START,	PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::CH,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::DG,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::LG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::SC,		PkLexFsmStates::LEX);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::NL,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LEX,		PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::CH,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::DG,		PkLexFsmStates::CON);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::LG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::NL,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::CON,		PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::LG,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::MN,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::EQ,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::TR,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::NL,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::TRM,		PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::LG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::SC,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::EQ,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::NL,		PkLexFsmStates::NLN);
			AddTransition(PkLexFsmStates::NLN,		PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::LG,		PkLexFsmStates::LOG2);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::EQ,		PkLexFsmStates::LOG2);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::TR,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::NL,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG,		PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);

			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::CH,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::DG,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::WS,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::LG,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::SC,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::MN,		PkLexFsmStates::START);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::EQ,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::TR,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::NL,		PkLexFsmStates::ERR);
			AddTransition(PkLexFsmStates::LOG2,		PkLexFsmEvents::UNK,	PkLexFsmStates::ERR);
		}

	public:
		bool Process(PkLang::TmPkOutLexems& lexems, PkLang::TmPkOutConsts& consts, PkLang::TvPkOutIdnts& idents, PkLang::TmErrors& errors)
		{
			size_t nLine = 1;
			size_t nIndex = 1;
			std::wstring lexema(L"");

			for (auto& itCh = m_sText.begin(); itCh != m_sText.end(); ++itCh)
			{
				wchar_t ch = *itCh;

				const auto& event = PkLexFsmEvent(*itCh);
				AcceptEvent(event);
				if (GetCurrentState().GetState() == PkLexFsmStates::START)
				{
					const auto prevState = GetPreviosState().GetState();

					if (prevState == PkLexFsmStates::NLN)
					{
						for (auto pos = lexema.find_first_of(L'\n', 0); pos != std::wstring::npos; pos = lexema.find_first_of(L'\n', ++pos))
							nLine++;
						lexema.erase();
						itCh--;
						continue;
					}
					else if (prevState == PkLexFsmStates::START)
					{
						lexema.erase();
						continue;
					}

					PkLang::PkOutLexema outLex;
					outLex.Name = lexema;
					outLex.Line = nLine;
					outLex.Index = nIndex++;
					outLex.Class = getLexType(lexema);
					outLex.Id = getLexId(lexema);

					if (prevState == PkLexFsmStates::LEX)
					{
						LOG("Found Lexema: " + std::string(lexema.begin(), lexema.end()));
						if (outLex.Id == 0
							&& std::find(idents.begin(), idents.end(), lexema) == idents.end())
						{
							PkLang::PkOutIdn ident;
							ident.Index = nIndex;
							ident.Name = lexema;
							ident.Type = PkLang::PkIdnTypes::Undef; // lexema.back() == L':' ? PkLang::PkIdnTypes::Lbl : PkLang::PkIdnTypes::Int; // dirty hack
							idents.push_back(ident);
						}
					}
					else if (prevState == PkLexFsmStates::CON)
					{
						outLex.Class = PkLang::PkLexemClasses::Const;

						LOG("Found Constant: " + std::string(lexema.begin(), lexema.end()));

						PkLang::PkOutConst outConst;
						outConst.Value = std::stoi(lexema);
						outConst.Index = nIndex;

						consts[nIndex] = outConst;
					}
					else if (prevState == PkLexFsmStates::TRM)
					{
						if (outLex.Id == 0)
						{
							wchar_t msg[512];
							swprintf_s(msg, 512, L"Syntax error at line %d. Unknown keyword \"%s\"", nLine, lexema.c_str());							
							LOG(wcs2cs(msg).c_str());
							errors[nLine].push_back(msg);
						}
						else
						{
							outLex.Class = PkLang::PkLexemClasses::Operator;

							LOG("Found Terminal: " + std::string(lexema.begin(), lexema.end()));
						}
					}
					else if (prevState == PkLexFsmStates::LOG || prevState == PkLexFsmStates::LOG2)
					{
						if (outLex.Id == 0)
						{
							wchar_t msg[512];
							swprintf_s(msg, 512, L"Syntax error at line %d. Unknown keyword \"%s\"", nLine, lexema.c_str());
							LOG(wcs2cs(msg).c_str());
							errors[nLine].push_back(msg);
						}
						else
						{
							outLex.Class = PkLang::PkLexemClasses::Operator;
							LOG("Found Logical: " + std::string(lexema.begin(), lexema.end()));
						}
					}

					lexems[nLine].push_back(outLex);

					lexema.erase();
					if (event != PkLexFsmEvents::WS)
						--itCh;
				}
				else if (GetCurrentState().GetState() == PkLexFsmStates::ERR)
				{
					wchar_t msg[512];
					swprintf_s(msg, 512, L"Syntax error at line %d.", nLine);
					errors[nLine].push_back(msg);
					LOG(wcs2cs(msg).c_str());
					while (PkLexFsmEvent(*(++itCh)) != PkLexFsmEvents::NL);
					itCh--;
					Reset(PkLexFsmStates::START);
				}
				else
				{
					lexema += *itCh;
				}
			}

			if (lexema.empty() == false && GetCurrentState().GetState() == PkLexFsmStates::START && GetPreviosState() != PkLexFsmStates::NLN)
			{
				LOG(std::string(lexema.begin(), lexema.end()));

				PkLang::PkOutLexema outLex;
				outLex.Name = lexema;

				lexems[nLine].push_back(outLex);
			}

			return true;
		}

	private:
		const PkLang::PkLexemClasses getLexType(const std::wstring& lexema) const
		{
			PkLang::PkLexemClasses res = PkLang::PkLexemClasses::Unknown;

			const auto& lex = std::find(PkLang::LEXEMS.begin(), PkLang::LEXEMS.end(), lexema);

			if (lex != PkLang::LEXEMS.end())
				res = lex->Class;

			return res;
		}

		const size_t getLexId(const std::wstring& lexema) const
		{
			size_t res = 0;

			const auto& lex = std::find(PkLang::LEXEMS.begin(), PkLang::LEXEMS.end(), lexema);

			if (lex != PkLang::LEXEMS.end())
				res = lex->Id;

			return res;
		}

		std::string wcs2cs(const std::wstring& str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
			return conv.to_bytes(str.c_str());
		}

	private:		
		std::wstring m_sText;
	};

}
