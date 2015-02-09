#include"RLEnc.h"

int FindSymbolPosition(Symbol *pSymTable, unsigned int cSym, int iTotSymbols);
void MoveSymbolToFront(Symbol *pSymTable, unsigned int cSym, int iTotSYmbols);
void PrintSymbolTable(Symbol *pSymTable, int iCount);

RLEnc::RLEnc()
{

}

RLEnc::RLEnc(FileStatistics *pFileStats)
{
	this->pFileStats = pFileStats;

	this->pSymTable = new Symbol[this->pFileStats->GetTotalSymbolCount()];

	// Fill Symbols and their Probabilities
	int j = 0;
	for (unsigned int i = 0; i < 256; i++)
	{
		if (this->pFileStats->GetProbability()[i] > 0.00f)
		{
			this->pSymTable[j].SetProbability(this->pFileStats->GetProbability()[i]);
			this->pSymTable[j].SetSymbol(i);

			// Add all the symbols to the nodeArray list
			/*Node tempNode(i, this->pSymTable[j].GetProbability(), true);
			this->nodeArray.push_back(tempNode);*/

			j++;
		}
	}
}

void RLEnc::Encode_RLE_Basic()
{
	string strOpFileName, strIpFileName;
	FILE *fpIn, *fpOut;
	unsigned int cSym;

	strIpFileName = this->pFileStats->szFileName;
	strOpFileName = GenerateOpFileName(strIpFileName, "_RLE_Basic_Op.dat");

	fpIn = fopen(strIpFileName.c_str(),"rb");
	fpOut = fopen(strOpFileName.c_str(), "wb");

	while ((cSym = fgetc(fpIn)) != EOF)
	{
		unsigned int cNext;
		int iCurrCount = 1;

		while (((cNext = fgetc(fpIn)) != EOF) && (cNext == cSym))
		{
			if (cNext == EOF)
				break;
			iCurrCount++;
		}

		/// For debugging
		//cout << "\ncSymbol: " << cSym << " Count: " << iCurrCount;

		fputc(iCurrCount, fpOut);
		fputc(cSym, fpOut);

		if (cNext != EOF)
			fseek(fpIn, -1, SEEK_CUR);
	}

	fclose(fpIn);
	fclose(fpOut);
}

void  RLEnc::Encode_RLE_Modified()
{
	string strOpFileName, strIpFileName;
	FILE *fpIn, *fpOut;
	unsigned int cSym;

	strIpFileName = this->pFileStats->szFileName;
	strOpFileName = GenerateOpFileName(strIpFileName, "_RLE_Modified_Op.dat");

	fpIn = fopen(strIpFileName.c_str(), "rb");
	fpOut = fopen(strOpFileName.c_str(), "wb");

	while ((cSym = fgetc(fpIn)) != EOF)
	{
		unsigned int cNext;
		int iCurrCount = 1;

		while (((cNext = fgetc(fpIn)) != EOF) && (cNext == cSym))
		{
			if (cNext == EOF)
				break;
			iCurrCount++;

			if (iCurrCount == 127)
				break;
		}

		if (iCurrCount == 1)
		{
			if ((cSym & 128) == 128)
			{
				unsigned int iPreCount = 129;
				fputc(iPreCount, fpOut);
				fputc(cSym, fpOut);
			}
			else
			{
				fputc(cSym, fpOut);
			}
		}
		else
		{
			unsigned int iPreCount = (1 << 7) | (iCurrCount);
			fputc(iPreCount, fpOut);
			fputc(cSym, fpOut);
		}		

		if (cNext != EOF)
			fseek(fpIn, -1, SEEK_CUR);
	}

	fclose(fpIn);
	fclose(fpOut);
}

void RLEnc::Decode_RLE_Modified(string strIpFileName)
{
	string strOpFileName;
	FILE *fpIn, *fpOut;
	unsigned int cSym;

	strIpFileName;
	strOpFileName = GenerateOpFileName(strIpFileName, "_RLE_Modified_Decode_Op.dat");

	fpIn = fopen(strIpFileName.c_str(), "rb");
	fpOut = fopen(strOpFileName.c_str(), "wb");

	while ((cSym = fgetc(fpIn)) != EOF)
	{
		// If MSB is 1
		/*if (cSym == 129)
		{
			unsigned int cPrintSym = fgetc(fpIn);
			fputc(cPrintSym, fpOut);

			continue;
		}*/
		if ((cSym & 128) == 128)
		{
			unsigned int iCount = 127 & cSym;

			// Get the symbol to be written
			unsigned int cPrintSym = fgetc(fpIn);
			if (cPrintSym == EOF)
				break;
			for (int i = 0; i < iCount; i++)
			{
				// Print the symbols in the op file
				fputc(cPrintSym, fpOut);
			}
		}
		else
		{
			fputc(cSym, fpOut);
		}
	}

	fclose(fpIn);
	fclose(fpOut);
}

void  RLEnc::Encode_RLE_MTFT()
{
	string strOpFile = GenerateOpFileName(this->pFileStats->szFileName, "_RLE_MTF_Op.dat");
	// Init the Symbol Table		
	FILE *fpIn = fopen(this->pFileStats->szFileName,"rb");
	FILE *fpOp = fopen(strOpFile.c_str(), "wb");

	unsigned int cSym;

	while ((cSym = fgetc(fpIn)) != EOF)
	{
		// Get cSym's position from Symbol Table
		int iPos = FindSymbolPosition(this->pSymTable, cSym, this->pFileStats->GetTotalSymbolCount());

		// Output this position
		putc(iPos, fpOp);		
		// Move cSym to the front of the symbol table
		if (iPos != 0)		
			MoveSymbolToFront(this->pSymTable, cSym, this->pFileStats->GetTotalSymbolCount());
	}

	fclose(fpIn);
	fclose(fpOp);
}

int FindSymbolPosition(Symbol *pSymTable, unsigned int cSym, int iTotSymbols)
{
	for (int i = 0; i < iTotSymbols; i++)
	{
		if (pSymTable[i].GetSymbol() == cSym)
			return (i);
	}
}

void MoveSymbolToFront(Symbol *pSymTable, unsigned int cSym, int iTotSymbols)
{
	int iPos = FindSymbolPosition(pSymTable, cSym, iTotSymbols);
	int iIndex = iPos;
	Symbol frontSym = pSymTable[iIndex];

	for (int i = iIndex; i > 0; i--)
	{
		pSymTable[i] = pSymTable[i-1];
	}

	pSymTable[0] = frontSym;
}

void PrintSymbolTable(Symbol *pSymTable, int iCount)
{
	for (int i = 0; i < iCount; i++)
		cout << ((char)(pSymTable[i].GetSymbol()));
}