#pragma once

#include <string>

namespace PkFSM
{
	template<typename States, class Event>
	class PkMachineState
	{
	public:
		PkMachineState(const PkMachineState& other) 
		{
			m_state = other.GetState();
		}

		PkMachineState(const States& state)
			: m_state(state)
		{ }

		virtual ~PkMachineState() {};

	public:
		const States GetState() const { return m_state; }

	public:
		const bool operator == (const PkMachineState& x) const
		{
			return (m_state == x.m_state);
		}

		const bool operator < (const PkMachineState& x) const
		{
			return (m_state < x.m_state);
		}

		operator const States () const
		{
			return m_state;
		}

		const PkMachineState& operator = (States s)
		{
			m_state = s;
			return *this;
		}

	public:
		virtual void OnEnter(PkMachineState& from, const Event& event)
		{
		}

		virtual void OnExit(const Event& event, PkMachineState& to)
		{
		}

	protected:
		void setState(const States& s)
		{
			m_state = s;
		}

	private:
		States m_state;		
	};
}
