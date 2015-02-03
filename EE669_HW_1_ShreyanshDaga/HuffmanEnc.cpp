#include "HW_1.h"
#include "HuffmanEnc.h"

HuffmanEnc::HuffmanEnc()
{	

}

HuffmanEnc::HuffmanEnc(FileStatistics *pFileStats)
{
	this->pFileStats = pFileStats;
	this->iSymCount = this->pFileStats->GetTotalSymbolCount();

	this->pSymTable = new Symbol[this->iSymCount];

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
	
	// Sort The Symbols
	// Ascending order

	this->SortSymbols();

}

void HuffmanEnc::SortSymbols()
{
	//Sort symbols according to probabilty
	// Ascending order

	for (int i = 0; i < this->iSymCount; i++)
	{
		for (int j = 0; j < this->iSymCount; j++)
		{
			if (this->pSymTable[j].GetProbability() > this->pSymTable[i].GetProbability())
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

void HuffmanEnc::Encode_Huffman()
{

}

void HuffmanEnc::PrintSymbolTable()
{
	string strFileName(this->pFileStats->szFileName);
	int iPos = strFileName.find('.');
	string strSymTableFileName = strFileName.substr(0, iPos) + "_H_SymTable.txt";
	FILE *fp = fopen(strSymTableFileName.c_str(), "w");

	fprintf(fp, "\n\n Symbol   :: Code");

	for (int i = 0; i < this->iSymCount; i++)
	{
		bitset<8> bSymbol(this->pSymTable[i].GetSymbol());


		fprintf(fp, "\n%s  ::  %s", bSymbol.to_string('0', '1').c_str(), this->pSymTable[i].GetCode().c_str());
	}

	fclose(fp);
}

void HuffmanEnc::WriteToFile()
{
	string strFileName(this->pFileStats->szFileName);
	int iPos = strFileName.find('.');
	string strOpFileName = strFileName.substr(0, iPos) + "_H_Comp.dat";

	FILE *fpOut = fopen(strOpFileName.c_str(), "wb");
	FILE *fpIn = fopen(this->pFileStats->szFileName, "rb");

	fseek(fpIn, 0, SEEK_END);
	int iFileSize = ftell(fpIn);
	fseek(fpIn, 0, SEEK_SET);

	for (int i = 0; i < iFileSize; i++)
	{
		unsigned int cSymbol = (unsigned int)fgetc(fpIn);
		string szCode = this->GetCodeForSymbol(cSymbol);
		fprintf(fpOut, "%s", szCode.c_str());
	}

	fclose(fpIn);
	fclose(fpOut);
}

void HuffmanEnc::WritePostStatistics()
{

}

string HuffmanEnc::GetCodeForSymbol(unsigned int cSym)
{
	return "";
}
