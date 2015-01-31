#include "HW_1.h"

class FileStatistics
{	
	private:
		char szFileName[30];
		char pSymbolTable[256][2];
		float pfProbability[256];
		int iTotalSymCount;
		float fEntropy;
		bool bStats;
		FILE *fp;

	public:
		FileStatistics();
		FileStatistics(char *pszFileName);

		void GenerateStatistics();
		void IncrementSymbolCount(char cSym);
		int GetSymbolCount(char cSym);
		float GetSymbolProbability(char cSym);
		float GetEntropy();
		void PrintSymbolTable(char *pszFileName);
};