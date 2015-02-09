#ifndef FILESTATISTICS_H
#define FILESTATISTICS_H

#include "HW_1.h"
#include "SymbolTable.h"

class FileStatistics
{	
	private:				
		float pfProbability[256];
		int iFileSize;
		float fEntropy;
		bool bStats;
		FILE *fp;

	public:
		char szFileName[30];
		SymbolTable *pSymTable;

		FileStatistics();
		FileStatistics(char *pszFileName);
		FileStatistics(string strFileName);

		void GenerateStatistics();
		void IncrementSymbolCount(char cSym);
		int GetSymbolCount(char cSym);
		int GetTotalSymbolCount();
		float GetSymbolProbability(unsigned int cSym);
		float* GetProbability();
		float GetEntropy();
		void PrintSymbolTable(char *pszOPFileName);
		void PrintStatistics(string szFileName);
		int GetFileSizeInBits();
};

#endif