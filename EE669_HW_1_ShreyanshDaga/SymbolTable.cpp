
#include "HW_1.h"
#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
	this->iSize = 0;
	this->iSymbolCount = 0;

	this->pSymbol = NULL;
	this->pSymCount = NULL;
}

SymbolTable::SymbolTable(int iSize)
{
	this->iSize = iSize;
	this->iSymbolCount = 0;
	
	// Allocate Memory
	this->pSymbol = new char[iSize];
	this->pSymCount = new int[iSize];

	// Init the symbol table
	for (int i = 0; i < iSize; i++)
	{
		this->pSymbol[i] = 0;
		this->pSymCount[i] = 0;
	}
}

void SymbolTable::AddSymbol(unsigned int cSymbol)
{	
	if (this->pSymCount[cSymbol] == 0)
	{
		this->pSymCount[cSymbol] = 1;
		this->iSymbolCount++;
	}
	else
		this->pSymCount[cSymbol]++;
}

int SymbolTable::GetSymbolCount(unsigned int cSymbol)
{
	return this->pSymCount[cSymbol];
}

int SymbolTable::GetTotalSymbolCount()
{
	return this->iSymbolCount;
}