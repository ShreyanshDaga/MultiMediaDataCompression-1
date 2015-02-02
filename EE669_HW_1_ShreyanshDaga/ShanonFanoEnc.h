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

	public:
		ShannonFanoEnc();
		ShannonFanoEnc(FileStatistics *pFileStats);
		void Encode_ShannonFano();
};

#endif