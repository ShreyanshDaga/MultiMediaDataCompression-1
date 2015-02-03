#ifndef HUFFMANENC_H_
#define HUFFMANENC_H_

#include "HW_1.h"
#include "FileStatistics.h"
#include "Symbol.h"

class HuffmanEnc
{
	private:
		FileStatistics *pFileStats;
		Symbol *pSymTable;
		int iSymCount;

		void SortSymbols();
		string GetCodeForSymbol(unsigned int cSym);

	public:
		HuffmanEnc();												//Empty Constructor
		HuffmanEnc(FileStatistics *pFileStats);						//Parameterised Constructor
		void Encode_Huffman();
		void PrintSymbolTable();
		void WriteToFile();
		void WritePostStatistics();
};

#endif