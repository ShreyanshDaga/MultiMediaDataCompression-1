#include"HW_1.h"
#include "FileStatistics.h"
#include "ShanonFanoEnc.h"
#include "HuffmanEnc.h"

// Entropy Coding

void Problem_2_A()
{
	// Shannon-Fano Coding

	FileStatistics fTest("test_2.txt");
	ShannonFanoEnc SFEnc_Test(&fTest);

	SFEnc_Test.Encode_ShannonFano();

	// i) For Text
	FileStatistics fText("text.dat");
	ShannonFanoEnc SFEnc_Text(&fText);

	SFEnc_Text.Encode_ShannonFano();

	// ii) For Audio
	FileStatistics fAudio("audio.dat");
	ShannonFanoEnc SFEnc_Aud(&fAudio);

	SFEnc_Aud.Encode_ShannonFano();

	// iii) For GreyScale Image
	FileStatistics fImage("image.dat.raw");
	ShannonFanoEnc SFEnc_Img(&fImage);

	SFEnc_Img.Encode_ShannonFano();

	// iv) For Binary Image
	FileStatistics fBinary("binary.dat.raw");
	ShannonFanoEnc SFEnc_Bin(&fBinary);

	SFEnc_Bin.Encode_ShannonFano();
}

void Problem_2_B()
{
	// Huffman Coding with Global Stats
	FileStatistics fTest("test_2.txt");
	HuffmanEnc HEnc_Test(&fTest);

	HEnc_Test.Encode_Huffman();

	// Huffman Coding with Global Stats
	FileStatistics fText("text.dat");
	HuffmanEnc HEnc_Text(&fText);

	HEnc_Text.Encode_Huffman();

	// Huffman Coding with Global Stats
	FileStatistics fAudio("audio.dat");
	HuffmanEnc HEnc_Audio(&fAudio);

	HEnc_Audio.Encode_Huffman();

	// Huffman Coding with Global Stats
	FileStatistics fImage("image.dat.raw");
	HuffmanEnc HEnc_Image(&fImage);

	HEnc_Image.Encode_Huffman();

	// Huffman Coding with Global Stats
	FileStatistics fBin("binary.dat.raw");
	HuffmanEnc HEnc_Bin(&fBin);

	HEnc_Bin.Encode_Huffman();
}

void Problem_2_C()
{

}