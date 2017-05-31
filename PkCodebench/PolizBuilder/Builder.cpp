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
			case PkLexemClasses::CON: m_poliz.push_back(itLex.Name);
				break;
			case PkLexemClasses::IDN: m_poliz.push_back(itLex.Name);
				break;
			case PkLexemClasses::TRM: 
			{
				if (m_stack.empty())
				{
					m_stack.push(itLex.Name);
				}
				else
				{
					while (m_stack.empty() == false && getPriority(m_stack.top()) >= getPriority(itLex.Name))
					{
						m_poliz.push_back(m_stack.top());
						m_stack.pop();
					}
					m_stack.push(itLex.Name);
				}				
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

const size_t Builder::getPriority(const std::wstring& lexem) const
{
	const auto& it = PRIORITY.find(lexem);
	if (it != PRIORITY.end())
		return it->second;

	return -100;
}