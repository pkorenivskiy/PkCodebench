#pragma once

#include "PkStateMachineException.h"

namespace PkFSM
{
	template <class PkMachineState>
	class PkThrowStrategy
	{
	public:
		void operator() (const SEvent &) const { throw PkStateMachineException("Unknown event."); }
	};
}