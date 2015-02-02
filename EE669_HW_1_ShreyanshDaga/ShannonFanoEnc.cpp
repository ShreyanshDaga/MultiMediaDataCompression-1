#include "HW_1.h"
#include "ShanonFanoEnc.h"

ShannonFanoEnc:: ShannonFanoEnc()
{
	this->pFileStats = NULL;
}

ShannonFanoEnc::ShannonFanoEnc(FileStatistics *pFileStats, int iSymCount)
{
	this->pFileStats = pFileStats;
	this->iSymCount = iSymCount;

	this->pSymTable = new Symbol[iSymCount];

}

void ShannonFanoEnc::Encode_ShannonFano()
{
	//Sort symbols according to probabilty

	
}

void ShannonFanoEnc::SortSymbols()
{

}