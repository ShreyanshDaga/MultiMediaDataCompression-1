#include "HW_1.h"
#include "FileStatistics.h"
#include "HuffmanEnc.h"

HuffmanEnc::HuffmanEnc()
{	

}

HuffmanEnc::HuffmanEnc(FileStatistics *pFileStats)
{
	this->pFileStats = pFileStats;
	this->iSymCount = this->pFileStats->GetTotalSymbolCount();
	this->pHuffmanTree = new Tree();

	this->pSymTable = new Symbol[this->iSymCount];	


	// Fill Symbols and their Probabilities
	int j = 0;
	for (unsigned int i = 0; i < 256; i++)
	{
		if (this->pFileStats->GetProbability()[i] > 0.00f)
		{
			this->pSymTable[j].SetProbability(this->pFileStats->GetProbability()[i]);
			this->pSymTable[j].SetSymbol(i);						

			// Add all the symbols to the nodeArray list
			Node tempNode(i,this->pSymTable[j].GetProbability(),true);
			this->nodeArray.push_back(tempNode);

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
	Node *pRoot;

	while (!this->nodeArray.empty())
	{
		Node *pTempNode = new Node();
		Node *pMin1 = new Node();
		Node *pMin2 = new Node();

		*pMin1 = this->ExtractMin();
		*pMin2 = this->ExtractMin();

		pTempNode->AddLeftChild(pMin1);
		pTempNode->AddRightChild(pMin2);
		pTempNode->fProb = pMin1->fProb + pMin2->fProb;

		this->nodeArray.push_back(*pTempNode);

		if (this->nodeArray.size() == 1)
		{
			// only root 
			pRoot = &this->nodeArray[0];
			break;
		}
	}

	// Assign Codes
	this->AssignCode(pRoot, "");
	
	// Print SymbolTable
	this->PrintSymbolTable();

	// Write Output File
	this->WriteToFile();
}

void HuffmanEnc::AssignCode(Node *pRoot, string strCode)
{	

	Node *root1 = new Node();
	root1 = pRoot;

	root1->strCode = strCode;

	if (root1 == NULL)
	{

	}
	else if (root1->pLeft == NULL && root1->pRight == NULL)
	{

		unsigned int cSym = root1->cSym;
		string strCode = root1->strCode;
		Symbol S;
		S.SetSymbol(cSym);
		S.AppendToCode(strCode);

		// Add to SymbolTable
		this->symTable.push_back(S);
		// For debug
		//cout << "\nSymbol: " << cSym << " Code: " << strCode;
	}
	else
	{

		root1->pLeft->strCode = strCode.append("0");
		strCode.erase(strCode.end() - 1);

		root1->pRight->strCode = strCode.append("1");
		strCode.erase(strCode.end() - 1);


		AssignCode(root1->pLeft, strCode.append("0"));
		strCode.erase(strCode.end() - 1);
		AssignCode(root1->pRight, strCode.append("1"));
		strCode.erase(strCode.end() - 1);
	}

	/*if (pRoot == NULL)	
		return;		
		
	pRoot->strCode = strCode;

	if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
	{
		unsigned int cSym = pRoot->cSym;
		string strCode = pRoot->strCode;

		cout << "\nSymbol: " << cSym << " Code: " << strCode;
	}

	AssignCode(pRoot->pLeft, pRoot->strCode + "0");
	AssignCode(pRoot->pRight, pRoot->strCode + "1");*/
}

Node HuffmanEnc::ExtractMin()
{
	// This will extract the minimum node from node array
	float fMax = (float)INT_MAX;

	vector<Node>::iterator i1, iPos;

	for (i1 = this->nodeArray.begin(); i1 != this->nodeArray.end(); i1++)
	{
		if (fMax > i1->fProb)
		{
			iPos = i1;
			fMax = i1->fProb;
		}
	}

	Node nodeMin = (*iPos);
	this->nodeArray.erase(iPos);

	return nodeMin;
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
		bitset<8> bSymbol(this->symTable[i].GetSymbol());

		fprintf(fp, "\n%s  ::  %s", bSymbol.to_string('0', '1').c_str(), this->symTable[i].GetCode().c_str());
	}

	fclose(fp);
}

void HuffmanEnc::WriteToFile()
{
	int iTotBitCount = 0;	

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
		iTotBitCount += szCode.length();		

		fprintf(fpOut, "%s", szCode.c_str());
	}

	fclose(fpIn);
	fclose(fpOut);
	
	WritePostStatistics(iTotBitCount);
}

void HuffmanEnc::WritePostStatistics(int iTotBitCount)
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
	string strOpFileName = strFileName.substr(0, iPos) + "_H_Comp.dat";
	string strOpStatsFileName = GenerateOpFileName(strOpFileName, "_Op_Stats.txt");
	
	FILE *fp = fopen(strOpStatsFileName.c_str(), "w");

	fprintf(fp, "Output File Statistics for Huffman Coding with Global Statistics\n");
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

string HuffmanEnc::GetCodeForSymbol(unsigned int cSym)
{
	for (int i = 0; i < this->iSymCount; i++)
	{
		if (cSym == this->symTable[i].GetSymbol())
			return this->symTable[i].GetCode();
	}
}
