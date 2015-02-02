#include "HW_1.h"
#include "ShanonFanoEnc.h"

ShannonFanoEnc:: ShannonFanoEnc()
{
	this->pFileStats = NULL;
}

ShannonFanoEnc::ShannonFanoEnc(FileStatistics *pFileStats)
{
	this->pFileStats = pFileStats;
	this->iSymCount = pFileStats->GetTotalSymbolCount();

	this->pSymTable = new Symbol[iSymCount];

	// Fill Symbols and their Probabilities
	for (unsigned int i = 0; i < 256; i++)
	{
		if (this->pFileStats->GetProbability()[i] > 0.00f)
		{
			this->pSymTable[i].SetProbability(this->pFileStats->GetProbability()[i]);
			this->pSymTable[i].SetSymbol(i);
		}
	}

	// Sort Symbols Accrording to Probabilities
	this->SortSymbols();
}

void ShannonFanoEnc::Encode_ShannonFano()
{		
}

void ShannonFanoEnc::SortSymbols()
{
	//Sort symbols according to probabilty

	for (int i = 0; i < this->iSymCount; i++)
	{
		for (int j = 0; j < this->iSymCount; j++)
		{
			if (this->pSymTable[j].GetProbability() < this->pSymTable[i].GetProbability())
			{
				float fTemp = this->pSymTable[i].GetProbability();
				unsigned int iTemp = this->pSymTable[i].GetSymbol();

				this->pSymTable[i].SetSymbol(this->pSymTable[j].GetProbability());
				this->pSymTable[i].SetProbability(this->pSymTable[j].GetSymbol());

				this->pSymTable[j].SetProbability(fTemp);
				this->pSymTable[j].SetSymbol(iTemp);
			}
		}
	}
}