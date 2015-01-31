
class SymbolTable
{
	private:
		int *pSymCount;
		char *pSymbol;
		int iSize;

	public:
		SymbolTable();
		SymbolTable(int iSize);
		void AddSymbol(char cSymbol);
		int GetSymbolCount(char cSymbol);
		int GetSize();
};