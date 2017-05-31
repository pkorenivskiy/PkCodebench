#include "stdafx.h"
#include "Builder.h"

#include "Priorities.h"

using namespace PkLang;

Builder::Builder(const TmPkOutLexems& lexems)
	: m_lexems(lexems)
{
}


Builder::~Builder()
{
}

bool Builder::Build()
{
	bool res = false;

	for (const auto& itLine : m_lexems)
	{
		if (itLine.second[0].Id == LNG_INT || itLine.second[0].Id == LNG_LABEL)
			continue;

		for (const auto itLex : itLine.second)
		{
			switch (itLex.Class)
			{
			case PkLexemClasses::CON: m_poliz.push_back(itLex);
				break;
			case PkLexemClasses::IDN: m_poliz.push_back(itLex);
				break;
			case PkLexemClasses::TRM: 
			{
				while (m_stack.empty() == false && getPriority(m_stack.top()) >= getPriority(itLex))
				{
					if (m_stack.top().Id != LNG_LBR)
						m_poliz.push_back(m_stack.top());
					m_stack.pop();
				}
				if (itLex.Id != LNG_RBR)
					m_stack.push(itLex);
			}
			break;
			default:
				break;
			}
		}
		while (m_stack.empty() == false)
		{
			m_poliz.push_back(m_stack.top());
			m_stack.pop();
		}
	}

	return res;
}

const size_t Builder::getPriority(const PkLang::PkOutLexema& lexem) const
{
	const auto& it = PRIORITY.find(lexem.Name);
	if (it != PRIORITY.end())
		return it->second;

	return -100;
}