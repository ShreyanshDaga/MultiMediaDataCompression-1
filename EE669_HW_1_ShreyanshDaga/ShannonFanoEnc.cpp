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
	int j = 0;
	for (unsigned int i = 0; i < 256; i++)
	{
		if (this->pFileStats->GetProbability()[i] > 0.00f)
		{
			this->pSymTable[j].SetProbability(this->pFileStats->GetProbability()[i]);
			this->pSymTable[j].SetSymbol(i);

			j++;
		}
	}

	// Sort Symbols Accrording to Probabilities
	this->SortSymbols();

	/// Prin sorted to command
	/*for (int i = 0; i < this->iSymCount; i++)
	{
		cout << "\n" << this->pSymTable[i].GetProbability();
	}
	getch();*/
}

void ShannonFanoEnc::Encode_ShannonFano()
{		
	this->ShannonRecursive(0, this->iSymCount - 1);
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

				this->pSymTable[i].SetSymbol(this->pSymTable[j].GetSymbol()); 
				this->pSymTable[i].SetProbability(this->pSymTable[j].GetProbability());

				this->pSymTable[j].SetProbability(fTemp);
				this->pSymTable[j].SetSymbol(iTemp);
			}
		}
	}
}

void ShannonFanoEnc::ShannonRecursive(int iStart, int iEnd)
{
	if (iStart >= iEnd)
		return;
	
	int iSet1 = 0, iSet2 = 0;
	int i0 = 0, i1 = 1;
	float fSum1 = 0.00f, fSum2 = 0.00f;

	iSet1 = iStart;
	iSet2 = iEnd;	
	
	while (iSet1 < iSet2)
	{
		fSum1 += this->pSymTable[iSet1].GetProbability();

		while (fSum2 < fSum1 && iSet2 > iSet1)
		{
			fSum2 += this->pSymTable[iSet2].GetProbability();
			iSet2--;
		}
		iSet1++;
	}	

	// First Set is iStart to iSet2, second set is from iSet2+1 to iEnd
	for (int i = iStart; i <= iSet2; i++)
	{
		this->pSymTable[i].AppendToCode("0");
	}

	for (int i = iSet2+1; i <= iEnd; i++)
	{
		this->pSymTable[i].AppendToCode("1");
	}

	this->ShannonRecursive(iStart,iSet2);
	this->ShannonRecursive(iSet2+1,iEnd);
}

void ShannonFanoEnc::PrintSymbolTable()
{
	FILE *fp = fopen("SymTable.txt","w");

	fprintf(fp, "\n\n Symbol   :: Code");

	for (int i = 0; i < this->iSymCount; i++)
	{
		bitset<8> bSymbol(this->pSymTable[i].GetSymbol());


		fprintf(fp, "\n%s  ::  %s", bSymbol.to_string('0', '1').c_str(), this->pSymTable[i].GetCode().c_str());
	}

	fclose(fp);
}

void ShannonFanoEnc::WriteToFile()
{
	FILE *fp = fopen("op.dat", "wb");

	for (int i = 0; i < this->iSymCount; i++)
	{
		fprintf(fp, "%s", this->pSymTable[i].GetCode().c_str());
	}

	fclose(fp);
}

void ShannonFanoEnc::WritePostStatistics()
{

}