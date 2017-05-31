#pragma once

#include <stack>
#include <string>
#include <vector>

class PkOutPoliz
{
public:
	const std::vector<std::wstring> GetPoliz() const { return m_poliz; }
	void SetPoliz(const std::vector<std::wstring>& poliz) { m_poliz = poliz; }
private:
	std::stack<std::wstring> m_stack;
	std::vector<std::wstring> m_poliz;
};
