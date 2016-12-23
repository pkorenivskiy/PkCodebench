#pragma once

enum SynStates
{
	ReadNexChar = 1,
	NewLine,
	ReadyLexema,
	ConstLexema,
	//OperLexema,
	InvalidLexema,
	Final
};