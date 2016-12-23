#pragma once

enum SynStates
{
	ReadNexChar = 1,
	NewLine,
	ReadyLexema,
	StartConst,
	InvalidLexema,
	Final
};