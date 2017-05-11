#pragma once

#include <string>

namespace PkLex
{
	enum PkLexFsmStates
	{
		START = 1,
		TRM,
		IDN,
		CON,
		OPR,
		LEX,
		ERR,
		NLN,
		END
	};



	class PkLexFsmBaseState
	{
	public:
		PkLexFsmBaseState(const PkLexFsmBaseState&) {} 

		PkLexFsmBaseState(const std::string& name)
			: m_sName(name)
		{ }

		const std::string& GetName() const { return m_sName; }

	public:
		virtual const bool operator == (const PkLexFsmBaseState& x) const
		{
			return (m_sName.compare(x.GetName()) == 0);
		}

	public:
		virtual ~PkLexFsmBaseState() {};

	private:
		std::string m_sName;
	};
}
