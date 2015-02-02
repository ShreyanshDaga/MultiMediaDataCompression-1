#include "HW_1.h"

class Symbol
{
	private:
		unsigned int cSymbol;
		float fProb;
		string strCode;

	public:
		Symbol();
		Symbol(unsigned int cSym, float fProb, string strCode);

		void AppendToCode(string cBit);
		void SetSymbol(unsigned int cSym);
		string GetCode();
		unsigned int GetSymbol();		
};