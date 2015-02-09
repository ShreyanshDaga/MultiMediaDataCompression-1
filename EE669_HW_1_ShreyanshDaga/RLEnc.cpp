#include"RLEnc.h"
#include"HuffmanEnc.h"
#include"ShanonFanoEnc.h"

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
	int iTotBits = 0;
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
		iTotBits += 16;

		if (cNext != EOF)
			fseek(fpIn, -1, SEEK_CUR);
	}

	fclose(fpIn);
	fclose(fpOut);

	this->WritePostStatistics(iTotBits, strOpFileName);

}

void  RLEnc::Encode_RLE_Modified()
{
	int iTotBits = 0;
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
				iTotBits += 16;
			}
			else
			{
				fputc(cSym, fpOut);
				iTotBits += 8;
			}
		}
		else
		{
			unsigned int iPreCount = (1 << 7) | (iCurrCount);
			fputc(iPreCount, fpOut);
			fputc(cSym, fpOut);
			iTotBits += 16;
		}		

		if (cNext != EOF && iCurrCount != 127)
			fseek(fpIn, -1, SEEK_CUR);
	}

	fclose(fpIn);
	fclose(fpOut);

	this->WritePostStatistics(iTotBits, strOpFileName);
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
		if (cSym == 129)
		{
			unsigned int cPrintSym = fgetc(fpIn);
			if (cPrintSym == EOF)
				break;
			fputc(cPrintSym, fpOut);
			continue;
		}

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
	string strOpFile = GenerateOpFileName(this->pFileStats->szFileName, "_MTF_Op.dat");
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

	// Perform RLE and other Encodings on this file
	FileStatistics fMTF1(strOpFile);
	FileStatistics fMTF2(strOpFile);
	FileStatistics fMTF3(strOpFile);

	RLEnc RLEnc(&fMTF1);
	HuffmanEnc HEnc(&fMTF2);
	ShannonFanoEnc SFEnc(&fMTF3);

	RLEnc.Encode_RLE_Basic();
	RLEnc.Encode_RLE_Modified();
	HEnc.Encode_Huffman();
	SFEnc.Encode_ShannonFano();
}

void RLEnc::Decode_RLE_MTFT()
{

}

void RLEnc::WritePostStatistics(int iTotBitCount, string strEncodedFile)
{
	float fCompressionRatio;

	fCompressionRatio = (float)(iTotBitCount) / (float)(this->pFileStats->GetFileSizeInBits());

	string strFileName(this->pFileStats->szFileName);
	int iPos = strFileName.find('.');
	string strOpFileName = strEncodedFile;
	string strOpStatsFileName = GenerateOpFileName(strOpFileName, "_Op_Stats.txt");

	FILE *fp = fopen(strOpStatsFileName.c_str(), "w");

	fprintf(fp, "Output File Statistics for RLE Coding\n");
	fprintf(fp, "\nInput FileName:    %s", strFileName.c_str());
	fprintf(fp, "\nOutput FileName:   %s", strEncodedFile.c_str());

	// Ip File Size
	fprintf(fp, "\nInput FileSize:    %d bits", this->pFileStats->GetFileSizeInBits());
	// Op File Size
	fprintf(fp, "\nOutput FileSize:   %d bits", iTotBitCount);
	// Compression Ratio
	fprintf(fp, "\nCompression Ratio: %f", fCompressionRatio);
	fprintf(fp, "\n  Savings :        %f %%", (1 - fCompressionRatio) * 100);

	fclose(fp);
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