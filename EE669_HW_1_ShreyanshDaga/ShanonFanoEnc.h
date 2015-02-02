#include "HW_1.h"
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
		ShannonFanoEnc(FileStatistics *pFileStats, int iSymCount);
		void Encode_ShannonFano();
};