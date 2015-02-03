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
	FileStatistics fText("test_1.dat");
	ShannonFanoEnc SFEnc(&fText);

	SFEnc.Encode_ShannonFano();
	SFEnc.PrintSymbolTable();
	SFEnc.WriteToFile();
	SFEnc.WritePostStatistics();

	// ii) For Audio
	FileStatistics fAudio("audio.dat");
	// iii) For GreyScale Image
	FileStatistics fImage("image.dat.raw");
	// iv) For Binary Image
	FileStatistics fBinary("binary.dat.raw");

	// Part b: ShannonFanoEncoder
	// i) For Text
	// ii) For Audio
	// iii) For GreyScale Image
	// iv) For Binary Image

	// Results
	// i) For Text
	// ii) For Audio
	// iii) For GreyScale Image
	// iv) For Binary Image
}

void Problem_2_B()
{
	// Huffman Coding with Global Stats

}

void Problem_2_C()
{
	// Huffman Coding with Locally Adaptive Statistics


}