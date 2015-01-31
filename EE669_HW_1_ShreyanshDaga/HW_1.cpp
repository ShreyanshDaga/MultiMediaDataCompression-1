#include "HW_1.h"

using namespace std;

int PrintMenu();

int main()
{	
	int iCh = 0;

	while (1)
	{
		iCh = PrintMenu();

		switch (iCh)
		{
			case 1:
				Problem_2_A();
			break;

			case 2:
				Problem_2_B();
			break;

			case 3:
				Problem_2_C();
			break;

			case 4:
				Problem_3_A();
			break;

			case 5:
				Problem_3_B();
			break;

			case 6:
				Problem_3_C();
			break;

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