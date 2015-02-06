#include"HW_1.h"
#include "FileStatistics.h"
#include "ShanonFanoEnc.h"
#include "HuffmanEnc.h"

// Entropy Coding

void Problem_2_A()
{
	// Shannon-Fano Coding

	// Part a: Entropy, Relative Frequency
	// i) For Text
	FileStatistics fText("text.dat");
	ShannonFanoEnc SFEnc_Text(&fText);

	SFEnc_Text.Encode_ShannonFano();
	SFEnc_Text.PrintSymbolTable();
	SFEnc_Text.WriteToFile();
	SFEnc_Text.WritePostStatistics();

	// ii) For Audio
	FileStatistics fAudio("audio.dat");
	ShannonFanoEnc SFEnc_Aud(&fAudio);

	SFEnc_Aud.Encode_ShannonFano();
	SFEnc_Aud.PrintSymbolTable();
	SFEnc_Aud.WriteToFile();
	SFEnc_Aud.WritePostStatistics();

	// iii) For GreyScale Image
	FileStatistics fImage("image.dat.raw");
	ShannonFanoEnc SFEnc_Img(&fImage);

	SFEnc_Img.Encode_ShannonFano();
	SFEnc_Img.PrintSymbolTable();
	SFEnc_Img.WriteToFile();
	SFEnc_Img.WritePostStatistics();

	// iv) For Binary Image
	FileStatistics fBinary("binary.dat.raw");
	ShannonFanoEnc SFEnc_Bin(&fBinary);

	SFEnc_Bin.Encode_ShannonFano();
	SFEnc_Bin.PrintSymbolTable();
	SFEnc_Bin.WriteToFile();
	SFEnc_Bin.WritePostStatistics();
}

void Problem_2_B()
{
	// Huffman Coding with Global Stats
	FileStatistics fText("test_1.txt");
	HuffmanEnc HEnc_Text(&fText);

	HEnc_Text.Encode_Huffman();

}

void Problem_2_C()
{
	// Huffman Coding with Locally Adaptive Statistics


}