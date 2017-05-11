#pragma once

#include <cwctype>

namespace PkLex
{
	enum PkLexFsmEvents
	{
		CH, // char
		DG, // digit
		WS, // white space
		NL, // new line

		UNK // unknown
	};

	class PkLexFsmEvent
	{
	public:
		PkLexFsmEvent(const wchar_t& ch)
			: m_Type(UNK)
		{
			if (std::iswalpha(ch))
				m_Type = CH;
			else if (std::iswdigit(ch))
				m_Type = DG;
			else if (ch == L'\r' || ch == L'\n')
				m_Type = NL;
			else if (std::iswspace(ch))
				m_Type = WS;
			else if (std::iswpunct(ch))
				m_Type = CH;
		}

		PkLexFsmEvent(const PkLexFsmEvent&) 
		{
		}
		virtual ~PkLexFsmEvent() {}

	public:
		const bool operator == (const PkLexFsmEvent& x) const
		{
			return true;
		}

		operator const PkLexFsmEvents () const 
		{ 
			return m_Type; 
		}

		const PkLexFsmEvent& operator = (PkLexFsmEvents e)
		{
			m_Type = e;
			return *this;
		}

	private:
		const PkLexFsmEvents GetType() const
		{
			return m_Type;
		}

	private:
		PkLexFsmEvents m_Type;
	};

}
