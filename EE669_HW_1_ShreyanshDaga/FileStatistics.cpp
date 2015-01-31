#include "HW_1.h"
#include "FileStatistics.h"

FileStatistics::FileStatistics()
{
	strcpy(this->szFileName, "");
	this->fEntropy = 0.00f;
	this->iTotalSymCount = 0;
	this->bStats = false;
	
}

FileStatistics::FileStatistics(char *pszFileName)
{
	this->fEntropy = 0.00f;
	this->iTotalSymCount = 0;
	this->bStats = false;	
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
		int iTotalBytes = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char c;

		for (int i = 0; i < iTotalBytes; i++)
		{
			unsigned int cByte = fgetc(fp);
						
			// Check if Symbol already there
			this->AddToSymbolTable(cByte);
		}

		this->bStats = true;
	}

}

void FileStatistics::IncrementSymbolCount(char cSym)
{

}

