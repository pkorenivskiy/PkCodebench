#pragma once

#include <stdexcept>

namespace PkFSM
{
	class PkStateMachineException : public std::exception
	{
	private:
		const std::string m_sMessage;

	public:
		PkStateMachineException(const std::string&  msg) : m_sMessage(msg) {}
		PkStateMachineException(const char* msg) : m_sMessage(msg) {}

		virtual const char* what(void) const throw() 
		{ 
			return m_sMessage.c_str(); 
		}
		virtual ~PkStateMachineException() throw () {}
	};
}

