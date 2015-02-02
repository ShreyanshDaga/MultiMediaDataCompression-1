#include "Symbol.h"

Symbol::Symbol()
{
	this->cSymbol = 0;
	this->strCode = "";
}

Symbol::Symbol(unsigned int cSym, float fProb, string strCode)
{
	this->cSymbol = cSym;
	this->strCode = strCode;
	this->fProb = fProb;
}

void Symbol::AppendToCode(string cBit)
{
	this->strCode = this->strCode + cBit;
}

void Symbol::SetSymbol(unsigned int cSym)
{
	this->cSymbol = cSym;
}

void Symbol::SetProbability(float fProb)
{
	this->fProb = fProb;
}

string Symbol::GetCode()
{
	return this->strCode;
}

unsigned int Symbol::GetSymbol()
{
	return this->cSymbol;
}

float Symbol::GetProbability()
{
	return this->fProb;
}