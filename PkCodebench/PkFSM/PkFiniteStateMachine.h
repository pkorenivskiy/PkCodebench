#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <memory>

#include "PkStateMachineException.h"
#include "PkStateMachineFunctors.h"
#include "../PkLogger/PkLoggerBase.h"

#define LOG(x) if (m_pLogger != nullptr) m_pLogger->Log(x)

namespace PkFSM
{
	template <class PkMachineState, class PkMachineEvent, class PkFunctor = PkEmptyFunctor<PkMachineState, PkMachineEvent>>
	class PkFiniteStateMachine
	{
	public:
		typedef PkMachineState StateType;
		typedef PkMachineEvent EventType;

	public:
		PkFiniteStateMachine(const StateType& startState)
			: m_CurrentState(startState)
			, m_PrevState(startState)
			, m_pLogger(nullptr)
		{
			m_vStates.push_back(startState);
		}

	public:
		void SetLogger(std::shared_ptr<PkLog::PkLoggerBase> pLogger)
		{
			m_pLogger = pLogger;
		}

		void Reset(const StateType& state)
		{
			m_PrevState = state;
			m_CurrentState = state;
		}

		void AddState(const StateType& state)
		{
			const auto& it = std::find(m_vStates.begin(), m_vStates.end(), state);
			if (it != m_vStates.end())
				throw PkStateMachineException("State must be unique.");

			m_vStates.push_back(state);
		}

		void AddTransition(const StateType& fromState, const EventType& event, const StateType& toState)
		{
			if (std::find(m_vStates.begin(), m_vStates.end(), fromState) == m_vStates.end())
				throw PkStateMachineException("FromState must be defined.");
			if (std::find(m_vStates.begin(), m_vStates.end(), toState) == m_vStates.end())
				throw PkStateMachineException("ToState must be defined.");

			auto it = std::find(m_vEvents.begin(), m_vEvents.end(), event);
			
			/*if (it != m_vEvents.end())
				throw PkStateMachineException("Event must be unique.");*/
			if (it == m_vEvents.end())
				m_vEvents.push_back(event);

			m_tblTrans[event][fromState] = toState;
		}

		void AcceptEvent(const EventType& event)
		{
			const auto& eventIt = m_tblTrans.find(event);

			if (eventIt == m_tblTrans.end())
				throw PkStateMachineException("Unknown event.");

			const auto& stateIt = eventIt->second.find(m_CurrentState);
			if (stateIt == eventIt->second.end())
				throw PkStateMachineException("No transition for this event from current state.");

			auto nextState = eventIt->second.find(m_CurrentState)->second; 

			m_Functor(m_CurrentState, event, nextState);

			if (nextState != m_CurrentState)
			{
				char lpszMsg[256];
				sprintf_s(lpszMsg, "Change state from %d to %d", (int)m_CurrentState, (int)nextState);
				LOG(lpszMsg);
				m_PrevState = m_CurrentState;
				m_CurrentState = nextState;				
			}
		}

		const StateType& GetCurrentState() const 
		{
			return m_CurrentState;
		}

		const StateType& GetPreviosState() const
		{
			return m_PrevState;
		}

	protected:
		std::shared_ptr<PkLog::PkLoggerBase> m_pLogger;

	private:
		typedef std::vector<StateType> VofStates;
		//typedef typename VofStates::const_iterator VofStatesCIt;

		typedef std::vector<EventType> VofEvents;
		//typedef typename VofEvents::const_iterator VofEventsCIt;

		typedef std::map<StateType, StateType> MapStateToState;
		typedef std::map<EventType, MapStateToState> TableTransition;
		//typedef typename TableTransition::const_iterator TableTransitionCIt;

	private:
		StateType m_CurrentState;
		StateType m_PrevState;
		VofStates m_vStates;
		VofEvents m_vEvents;
		PkFunctor m_Functor;
		TableTransition m_tblTrans; // A table of transitions between states
	};
}
