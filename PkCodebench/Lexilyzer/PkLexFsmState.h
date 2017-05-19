#pragma once

#include <string>

#include "PkLexFsmEvent.h"

#include "../PkFSM/PkMachineState.h"

namespace PkLex
{
	enum PkLexFsmStates
	{
		START = 1,
		END,
		LEX,
		CON,
		TRM,
		NLN,
		LOG,
		LOG2,
		CMT, //comment //
		ERR
	};

	class PkLexFsmState : public PkFSM::PkMachineState<PkLexFsmStates, PkLexFsmEvent>
	{
	public:
		//PkLexFsmState(const PkLexFsmState& other)
		//	: PkFSM::PkMachineState<PkLexFsmStates, PkLexFsmEvent>(other)
		//	//, m_bComplete(false)
		//	//, m_sLexema(L"")
		//{ }

		PkLexFsmState(const PkLexFsmStates& state)
			: PkFSM::PkMachineState<PkLexFsmStates, PkLexFsmEvent>(state)
			//, m_bComplete(false)
			//, m_sLexema(L"")
		{ }

		PkLexFsmState()
			: PkFSM::PkMachineState<PkLexFsmStates, PkLexFsmEvent>(START)
			//, m_bComplete(false)
			//, m_sLexema(L"")
		{
			setState(START);
		}

	/*public:
		bool IsComplete() const { return m_bComplete; }

	public:
		virtual void OnEnter(PkMachineState& from, const PkLexFsmEvent& event) override
		{
			m_sLexema.erase();
			m_bComplete = false;
		}

		virtual void OnExit(const PkLexFsmEvent& event, PkMachineState& to) override
		{
			m_sLexema += event;
			if (*this != to)
				m_bComplete = true;
		}

	private:
		std::wstring m_sLexema;
		bool m_bComplete;*/
	};
}
