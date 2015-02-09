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
		Symbol *pSymTable;
		
		RLEnc();
		RLEnc(FileStatistics *pFileStats);

		void Encode_RLE_Basic();
		void Encode_RLE_Modified();
		void Decode_RLE_Modified(string strIpFileName);
		void Encode_RLE_MTFT();
		void Decode_RLE_MTFT();

		void WritePostStatistics(int iTotBitCount, string strEncodedFile);
};

#endif