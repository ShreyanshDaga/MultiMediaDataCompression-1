#include<map>

class SymbolTable
{
	private:
		std::map<char,int> SymMap;
		int *pSymCount;
		char *pSymbol;
		int iSize;
		int iSymbolCount;

	public:
		SymbolTable();
		SymbolTable(int iSize);
		void AddSymbol(char cSymbol);
		int GetSymbolCount(char cSymbol);
		int GetTotalSymbolCount();
};