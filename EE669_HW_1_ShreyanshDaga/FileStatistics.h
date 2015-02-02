#ifndef FILESTATISTICS_H
#define FILESTATISTICS_H

#include "HW_1.h"
#include "SymbolTable.h"

class FileStatistics
{	
	private:
		char szFileName[30];
		SymbolTable *pSymTable;
		float pfProbability[256];
		int iFileSize;
		float fEntropy;
		bool bStats;
		FILE *fp;

	public:
		FileStatistics();
		FileStatistics(char *pszFileName);

		void GenerateStatistics();
		void IncrementSymbolCount(char cSym);
		int GetSymbolCount(char cSym);
		int GetTotalSymbolCount();
		float GetSymbolProbability(char cSym);
		float* GetProbability();
		float GetEntropy();
		void PrintSymbolTable(char *pszOPFileName);
		void PrintStatistics(string szFileName);
};

#endif