#include "HW_1.h"
#ifndef SHANONFANOENC_H_
#define SHANONFANOENC_H_

#include "FileStatistics.h"
#include "Symbol.h"

class ShannonFanoEnc
{
	private:
		FileStatistics *pFileStats;
		Symbol *pSymTable;
		int iSymCount;

		void SortSymbols();
		void ShannonRecursive(int iStart, int iEnd);
		string GetCodeForSymbol(unsigned int cSym);
	public:
		ShannonFanoEnc();
		ShannonFanoEnc(FileStatistics *pFileStats);
		void Encode_ShannonFano();
		void PrintSymbolTable();
		void WriteToFile();
		void WritePostStatistics();
};

#endif