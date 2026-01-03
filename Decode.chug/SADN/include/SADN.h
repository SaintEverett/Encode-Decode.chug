#ifndef SADN_H
#define SADN_H

#include "DecoderBase.h"

template <const unsigned order_>
class SADN : public Decoder<order_>
{
public:
	SADN()
	{
		efactor = 2.f * 3.14159265;
		efactor = sqrtf((efactor / (float)this->n_channels));
	}
	void tick(SAMPLE *in, SAMPLE *out, unsigned nframes) override
	{
		memset(out, 0, sizeof(SAMPLE) * this->n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++)							 // go through each frame
		{
			for (int c = 0; c < this->n_channels; c++) // go through each channel
			{
				SAMPLE sumd = 0;
				for (int n = 0; n < this->n_channels; n++) // each channel of the incoming stream is a spherical harmonic
				{
					sumd += (efactor * this->channelBalance * in[f * this->n_channels + n] * this->SpeakSH[c][n]); // matrix mult of speaker SHs and input stream
				}
				out[f * this->n_channels + c] = sumd;
			}
		}
	}

	void setPreservation(bool is3d)
	{
		if (is3d)
		{
			efactor = 4.f * 3.14159265;
			efactor = sqrtf((efactor / (float)this->n_channels));
		}
		else
		{
			efactor = 2.f * 3.14159265;
			efactor = sqrtf((efactor / (float)this->n_channels));
		}
	}

public:
	float efactor = 0.f;
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD1 : public SADN<1> // wrapper for SADN to chuck
{
public:
	SAD1(t_CKFLOAT fs) {};
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD2 : public SADN<2>
{
public:
	SAD2(t_CKFLOAT fs) {};
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD3 : public SADN<3>
{
public:
	SAD3(t_CKFLOAT fs) {};
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD4 : public SADN<4>
{
public:
	SAD4(t_CKFLOAT fs) {};
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD5 : public SADN<5>
{
public:
	SAD5(t_CKFLOAT fs) {};
};

#endif /* SADN_H */