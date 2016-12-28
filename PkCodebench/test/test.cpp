// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

#include "cbtypes.h"
#include "../Syntalyzer/Syntalyzer.h"

class foo
{
public:
	size_t n;
};

int main()
{
	CSyntalyzer syntalizer;
	
	std::vector<foo> vfoo;
	
	foo f1{ 1 }, f2{ 2 }, f3{ 3 };
	vfoo.push_back(f1);
	vfoo.push_back(f2);
	vfoo.push_back(f3);

	auto it = vfoo.begin();
	it++;
	it = it + 1;

	{
		char* a = new char[45];
	}
	
	auto errors = syntalizer.GetErrors();


	_CrtDumpMemoryLeaks();

    return 0;
}

