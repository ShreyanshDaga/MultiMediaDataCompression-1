#ifndef RLENC_H_
#define RLENC_H_

#include"HW_1.h"
#include"FileStatistics.h"
#include"Symbol.h"
#include"SymbolTable.h"

class RLEnc
{
	public:
		FileStatistics *pFileStats;
		
		RLEnc();
		RLEnc(FileStatistics *pFileStats)
};

#endif