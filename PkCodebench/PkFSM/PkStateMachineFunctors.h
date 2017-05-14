#pragma once


namespace PkFSM
{
	template <class PkMachineState, class PkMachineEvent>
	class PkEmptyFunctor
	{
	public:
		void operator() (PkMachineState& /*from*/, const PkMachineEvent& /*event*/, PkMachineState& /*to*/) 
		{ 
			return; 
		}
	};

	template <class PkMachineState, class PkMachineEvent>
	class PkOnEnterFunctor
	{
	public:
		void operator() (PkMachineState& from, const PkMachineEvent& event, PkMachineState& to)
		{
			to.OnEnter(from, event);
		}
	};

	template <class PkMachineState, class PkMachineEvent>
	class PkOnExitFunctor
	{
	public:
		void operator() (PkMachineState& from, const PkMachineEvent& event, PkMachineState& to)
		{
			from.OnExit(event, to);
		}
	};

	template <class PkMachineState, class PkMachineEvent>
	class PkOnMoveFunctor
	{
	public:
		void operator() (PkMachineState& from, const PkMachineEvent& event, PkMachineState& to)
		{
			from.OnExit(event, to); 
			to.OnEnter(from, event);
		}
	};
}