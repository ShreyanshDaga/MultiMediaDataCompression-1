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
}

void ShannonFanoEnc::Encode_ShannonFano()
{		
	this->ShannonRecursive(0, this->iSymCount - 1);

	// Print SymbolTable
	this->PrintSymbolTable();

	// Write Output File
	this->WriteToFile();
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
	string strFileName(this->pFileStats->szFileName);
	int iPos = strFileName.find('.');
	string strSymTableFileName = strFileName.substr(0, iPos) + "_SF_SymTable.txt";
	
	FILE *fp = fopen(strSymTableFileName.c_str(), "w");

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
	int iTotBitCount = 0;

	string strFileName(this->pFileStats->szFileName);
	int iPos = strFileName.find('.');
	string strOpFileName = strFileName.substr(0, iPos) + "_SF_Comp.dat";

	FILE *fpOut = fopen(strOpFileName.c_str(), "wb");
	FILE *fpIn = fopen(this->pFileStats->szFileName,"rb");
	
	fseek(fpIn, 0, SEEK_END);
	int iFileSize = ftell(fpIn);
	fseek(fpIn, 0, SEEK_SET);

	for (int i = 0; i < iFileSize; i++)
	{
		unsigned int cSymbol = (unsigned int)fgetc(fpIn);
		string szCode = this->GetCodeForSymbol(cSymbol);
		iTotBitCount += szCode.length();

		fprintf(fpOut, "%s", szCode.c_str());
	}

	fclose(fpIn);
	fclose(fpOut);

	WritePostStatistics(iTotBitCount);
}

void ShannonFanoEnc::WritePostStatistics(int iTotBitCount)
{
	float fCompressionRatio;
	float fRedundancy;
	float fAvgBits = 0.00f;

	fCompressionRatio = (float)(iTotBitCount) / (float)(this->pFileStats->GetFileSizeInBits());

	for (int i = 0; i < this->iSymCount; i++)
	{
		unsigned int cSym = this->pSymTable[i].GetSymbol();
		string szCode = this->GetCodeForSymbol(cSym);

		fAvgBits += this->pFileStats->GetSymbolProbability(cSym) * szCode.length();
	}

	fRedundancy = fAvgBits - this->pFileStats->GetEntropy();

	string strFileName(this->pFileStats->szFileName);
	int iPos = strFileName.find('.');
	string strOpFileName = strFileName.substr(0, iPos) + "_SF_Comp.dat";
	string strOpStatsFileName = GenerateOpFileName(strOpFileName, "_Op_Stats.txt");

	FILE *fp = fopen(strOpStatsFileName.c_str(), "w");

	fprintf(fp, "Output File Statistics for Shannon Fano Coding\n");
	fprintf(fp, "\nInput FileName:    %s", strFileName.c_str());
	fprintf(fp, "\nOutput FileName:   %s", strOpFileName.c_str());

	// Ip File Size
	fprintf(fp, "\nInput FileSize:    %d bits", this->pFileStats->GetFileSizeInBits());
	// Op File Size
	fprintf(fp, "\nOutput FileSize:   %d bits", iTotBitCount);
	// Compression Ratio
	fprintf(fp, "\nCompression Ratio: %f", fCompressionRatio);
	fprintf(fp, "\n  Savings :        %f %%", (1 - fCompressionRatio) * 100);
	// Average Bits
	fprintf(fp, "\nAverage Bits:      %f bits", fAvgBits);
	// Redundancy	
	fprintf(fp, "\nCoding Redundancy: %f", fRedundancy);

	fclose(fp);
}

string ShannonFanoEnc::GetCodeForSymbol(unsigned int cSym)
{
	for (int i = 0; i < this->iSymCount; i++)
	{
		if (this->pSymTable[i].GetSymbol() == cSym)
			return this->pSymTable[i].GetCode();
	}

	return "";
}