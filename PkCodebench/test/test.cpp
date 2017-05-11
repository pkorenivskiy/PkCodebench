// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <map>

#include "../PkLangDefs/PkLang.h"

class foo
{
public:
	size_t n;
	bool operator < (const foo& x) const { return false; }
};

template <typename T>
class bar
{
public:
	bar()
	{
	}

	~bar()
	{
	}

private:
};

class class2 : public bar<foo>
{
public:


private:

};



int main()
{
	std::map<foo, int> myMap;
	
	foo foo1, foo2;
	myMap[foo1] = 10;
	myMap[foo2] = 10;


	int aaa(5);

	aaa++;

	return 0;

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

