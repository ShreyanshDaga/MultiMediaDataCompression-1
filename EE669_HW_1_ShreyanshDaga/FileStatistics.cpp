#include "HW_1.h"
#include "FileStatistics.h"

FileStatistics::FileStatistics()
{
	strcpy(this->szFileName, "");
	this->fEntropy = 0.00f;	
	this->bStats = false;
	this->iFileSize = 0;
}

FileStatistics::FileStatistics(char *pszFileName)
{
	this->fEntropy = 0.00f;	
	this->bStats = false;	
	this->iFileSize = 0;
	this->pSymTable = new SymbolTable(256);

	strcpy(this->szFileName, pszFileName);

	// Generate the Statistics here
	this->GenerateStatistics();	
}

void FileStatistics::GenerateStatistics()
{
	if (!this->bStats)
	{
		// Read the file
		fp = fopen(this->szFileName, "rb");

		// Generate SymbolTable
		fseek(fp, 0, SEEK_END);
		// Find total number of bytes
		this->iFileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);		

		for (int i = 0; i < this->iFileSize; i++)
		{
			unsigned int cByte = (unsigned int)fgetc(fp);

			// Add the Symbol to the symbol table
			this->pSymTable->AddSymbol(cByte);
		}

		// Generate Probability
		for (int i = 0; i < 256; i++)
		{
			if (this->pSymTable->pSymCount[i] != 0)
			{
				this->pfProbability[i] = ((float)this->pSymTable->pSymCount[i] / this->iFileSize);
			}
			else
				this->pfProbability[i] = -1.00f;
		}

		// Calculate Entropy
		this->fEntropy = 0.00f;
		for (int i = 0; i < 256; i++)
		{
			if (this->pfProbability[i] > 0.00f)
				this->fEntropy += -(this->pfProbability[i]*log10f(this->pfProbability[i])/log10f(2.00f));
		}

		fclose(fp);
		// Statistics have been calculated
		this->bStats = true;
		string strFileName(this->szFileName);
		int iPos = strFileName.find('.');
		string strOpFileName = strFileName.substr(0, iPos) + "_Stats.txt";
		this->PrintStatistics(strOpFileName);
	}

}

void FileStatistics::IncrementSymbolCount(char cSym)
{

}

void FileStatistics::PrintStatistics(string szOpFileName)
{
	FILE *fp = fopen(szOpFileName.c_str(), "w");

	fprintf(fp, "Input File Name: %s", this->szFileName);
	fprintf(fp, "\nEntropy: %f", this->fEntropy);
	fprintf(fp, "\nTotal Symbols: %d", this->pSymTable->iSymbolCount);
	fprintf(fp, "\n\nSymbol(Binary) : Relative Frequnecy");

	for (int i = 0; i < 256; i++)
	{
		if (this->pfProbability[i] > 0.00)
		{
			bitset<8> byte(i);			
			float fP = this->pfProbability[i];
			
			string szProb = to_string(fP);
			string szSymbol = byte.to_string('0', '1');
			string szFinal = "\n" + szSymbol + " : " + szProb;
			
			fprintf(fp,"%s", szFinal.c_str());
		}
	}

	fclose(fp);
}

float* FileStatistics::GetProbability()
{
	return this->pfProbability;
}

int FileStatistics::GetTotalSymbolCount()
{
	return this->pSymTable->iSymbolCount;
}