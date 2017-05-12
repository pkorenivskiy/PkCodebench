#pragma once

#include <cwctype>

namespace PkLex
{
	enum PkLexFsmEvents
	{
		CH, // char
		DG, // digit
		WS, // white space
		
		LG, // !><
		SC, // :
		MN, // -
		EQ, // =
		TR, // other (',', ^, +, *, /

		NL, // new line (\r, \n)

		UNK // unknown
	};

	class PkLexFsmEvent
	{
	public:
		PkLexFsmEvent(const wchar_t& ch)
			: m_Type(UNK)
		{
			if (std::iswalpha(ch) || ch == L'_')
				m_Type = CH;
			else if (std::iswdigit(ch))
				m_Type = DG;
			else if (ch == L'\r' || ch == L'\n')
				m_Type = NL;
			else if (std::iswspace(ch))
				m_Type = WS;
			else if (std::wstring(L"!<>").find(ch) != std::wstring::npos)
				m_Type = LG;
			else if (ch == L':')
				m_Type = SC;
			else if (ch == L'-')
				m_Type = MN;
			else if (ch == L'=')
				m_Type = EQ;
			else if (std::wstring(L",^+*/()").find(ch) != std::wstring::npos)
				m_Type = TR;
			//else if (std::iswpunct(ch))
				//m_Type = CH;
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
