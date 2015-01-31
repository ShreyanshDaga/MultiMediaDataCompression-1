#include "HW_1.h"
#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
	this->iSize = 0;
	this->pSymbol = NULL;
	this->pSymCount = NULL;
}

SymbolTable::SymbolTable(int iSize)
{
	this->iSize = iSize;

	// Allocate Memory
	this->pSymbol = new char[iSize];
	this->pSymCount = new int[iSize];
}