// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cbtypes.h"
#include "../Syntalizer/Syntalizer.h"

int main()
{
	CSyntalizer syntalizer;
	
	{
		char* a = new char[45];
	}
	
	auto errors = syntalizer.GetErrors();


	_CrtDumpMemoryLeaks();

    return 0;
}

