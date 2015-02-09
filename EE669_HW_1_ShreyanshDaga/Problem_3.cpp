#include"HW_1.h"
#include "RLEnc.h"

// Entropy Coding

void Problem_3_A()
{
	// RLE Basic Scheme
	FileStatistics fText("text.dat");
	RLEnc RL_Enc_Text(&fText);

	RL_Enc_Text.Encode_RLE_Basic();

	FileStatistics fAudio("audio.dat");
	RLEnc RL_Enc_Aud(&fAudio);

	RL_Enc_Aud.Encode_RLE_Basic();

	FileStatistics fImage("image.dat.raw");
	RLEnc RL_Enc_Img(&fImage);

	RL_Enc_Img.Encode_RLE_Basic();

	FileStatistics fBinary("binary.dat.raw");
	RLEnc RL_Enc_Bin(&fBinary);

	RL_Enc_Bin.Encode_RLE_Basic();
}

void Problem_3_B()
{
	// RLE Modified Scheme
	FileStatistics fText("text.dat");
	RLEnc RL_Enc_Text(&fText);

	RL_Enc_Text.Encode_RLE_Modified();
	RL_Enc_Text.Decode_RLE_Modified("text_RLE_Modified_Op.dat");

	FileStatistics fBin("binary.dat.raw");
	RLEnc RL_Enc_Bin(&fBin);

	RL_Enc_Bin.Encode_RLE_Modified();
	RL_Enc_Bin.Decode_RLE_Modified("binary_RLE_Modified_Op.dat");
}

void Problem_3_C()
{
	//	RLE Move to Front
	FileStatistics fText("text.dat");
	RLEnc RL_Enc_Text(&fText);

	RL_Enc_Text.Encode_RLE_MTFT();

	FileStatistics fAudio("audio.dat");
	RLEnc RL_Enc_Audio(&fAudio);

	RL_Enc_Audio.Encode_RLE_MTFT();

	FileStatistics fImage("image.dat.raw");
	RLEnc RL_Enc_Image(&fImage);

	RL_Enc_Image.Encode_RLE_MTFT();

	FileStatistics fBin("binary.dat.raw");
	RLEnc RL_Enc_Bin(&fBin);

	RL_Enc_Bin.Encode_RLE_MTFT();	
}