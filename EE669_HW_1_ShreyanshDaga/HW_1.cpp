#include "HW_1.h"

using namespace std;

int PrintMenu();
void Split();
void TestForfeof();

int main()
{	
	int iCh = 0;
	///
	//	Split();
	//	TestForfeof();
	///
	while (1)
	{
		iCh = PrintMenu();

		switch (iCh)
		{
			case 1:
				Problem_2_A();
			//break;

			case 2:
				Problem_2_B();
			//break;

			case 3:
				Problem_2_C();
			//break;

			case 4:
				Problem_3_A();
			//break;

			case 5:
				Problem_3_B();
			//break;

			case 6:
				Problem_3_C();
			//break;

			case 0:
				exit(0);
			break;
		}
	}
}

int PrintMenu()
{
	int iCh = 0;

	system("CLS");
	cout << "\t\tShreyansh Daga, USCID 6375334833\n\n";
	cout << "******* Home work 1 ********\n";
	cout << "*  Problem 2:Entropy Coding\n";
	cout << "1. Q2(a) Shannon-Fano Coding\n";
	cout << "2. Q2(b) Huffman Coding with Global Statistics\n";
	cout << "3. Q2(c) Huffman Coding with Locally Adaptive Statistics\n\n";
	cout << "*  Problem 3:Run Length Encoding\n";
	cout << "4. Q3(a) RLE Basic Scheme\n";
	cout << "5. Q3(b) RLE Modified Scheme\n";
	cout << "6. Q3(c) RLE Move-to-Front Transform\n\n";
	cout << "0. Exit\n\n";
	cout << "\nEnter your choice: ";
	cin >> iCh;

	return iCh;
}

void Split()
{
	int iArray[2] = { 1, 1 };
	
	int i=0, j=1;
	int Sum1 = 0, Sum2 = 0;

	while (i < j)
	{		
		Sum1 += iArray[i];

		while (Sum2 < Sum1 && j > i)
		{			
			Sum2 += iArray[j];			
			j--;
		}		
		i++;
	}

	cout << i<<endl;
	cout << j<<endl;
}

string GenerateOpFileName(string strIpFileName, string strAppendText)
{
	
	int iPos = strIpFileName.find('.');
	string strOpFileName = strIpFileName.substr(0, iPos) + strAppendText;

	return strOpFileName;
}

void TestForfeof()
{
	FILE *fpIn = fopen("test_2.txt", "rb");
	unsigned int cSym;

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
		
		cout << "\ncSymbol: " << cSym << " Count: " << iCurrCount;
		
		if (cNext != EOF)
			fseek(fpIn, -1, SEEK_CUR);
	}
}