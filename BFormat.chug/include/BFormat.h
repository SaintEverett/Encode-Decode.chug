#ifndef BFORMAT_H
#define BFORMAT_H

#include "chugin.h"

template <unsigned int order_>
class BFormat
{
public:
	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear
		for (int f = 0; f < nframes; f++)
		{
			for (int i = 0; i < channel_count; i++)
			{
				out[f * channel_count + i] = (in[f * channel_count + i] * gain); // just add a gain factor to it 
			}
		}
	}

	void setGain(float n_gain)
	{
		gain = n_gain;
	}

	float getGain() { return gain; }

public:
	float gain = 0.0;
	constexpr static unsigned order = order_;
	constexpr static unsigned channel_count = (order_ + 1) * (order_ + 1);
};

class BFormat1 : public BFormat<1> // these simply just act as wrappers of BFormat to chuck
{
public:
	BFormat1(t_CKFLOAT fs) {};
};

class BFormat2 : public BFormat<2>
{
public:
	BFormat2(t_CKFLOAT fs) {};
};

class BFormat3 : public BFormat<3>
{
public:
	BFormat3(t_CKFLOAT fs) {};
};

class BFormat4 : public BFormat<4>
{
public:
	BFormat4(t_CKFLOAT fs) {};
};

class BFormat5 : public BFormat<5>
{
public:
	BFormat5(t_CKFLOAT fs) {};
};

#endif
