#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class SymbolTable
{
	public:		
		int *pSymCount;				// This stores the count of each symbol
		char *pSymbol;				// This stores the code of each symbol
		int iSize;					
		int iSymbolCount;

	public:
		SymbolTable();
		SymbolTable(int iSize);
		void AddSymbol(unsigned int cSymbol);
		int GetSymbolCount(unsigned int cSymbol);
		int GetTotalSymbolCount();
};

#endif