#pragma once

enum SynStates
{
	ReadNexChar = 1,
	NewLine,
	ReadyLexema,
	
	TRM,
	IDN,
	CON,
	OPR, // operator 

	InvalidLexema,
	Final
};