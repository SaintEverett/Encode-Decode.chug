#ifndef DECODEN_H
#define DECODEN_H

#include "DecoderBase.h"

template <const unsigned order_>
class Decode : public Decoder<order_> // seems redundant, but essentially takes all decoder commonalities, gives to this "Basic decoder" class with a sampling tick function
{
public:
	constexpr void tick(SAMPLE *in, SAMPLE *out, unsigned nframes) override
	{
		memset(out, 0, sizeof(SAMPLE) * this->n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++)							 // go through each frame
		{
			for (int c = 0; c < this->n_channels; c++) // go through each channel
			{
				SAMPLE sumd = 0;
				for (int n = 0; n < this->n_channels; n++) // each channel of the incoming stream is a spherical harmonic
				{
					sumd += (this->channelBalance * in[f * this->n_channels + n] * this->SpeakSH[c][n]); // matrix mult of speaker SHs and input stream
				}
				out[f * this->n_channels + c] = sumd;
			}
		}
	}
};

// this is actually what gets called and used by the chugin
class Decode1 : public Decode<1>
{
public:
	Decode1(t_CKFLOAT fs) {};
};

class Decode2 : public Decode<2>
{
public:
	Decode2(t_CKFLOAT fs) {};
};

class Decode3 : public Decode<3>
{
public:
	Decode3(t_CKFLOAT fs) {};
};

class Decode4 : public Decode<4>
{
public:
	Decode4(t_CKFLOAT fs) {};
};

class Decode5 : public Decode<5>
{
public:
	Decode5(t_CKFLOAT fs) {};
};

#endif