#ifndef ORDERGAIN_H
#define ORDERGAIN_H

#include "chugin.h"

template <unsigned int order_>
class OrderGain
{
public:
	void tick(SAMPLE *in, SAMPLE *out, unsigned nframes)
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
	float gain = 1.0;
	constexpr static unsigned order = order_;
	constexpr static unsigned channel_count = (order_ + 1) * (order_ + 1);
};

class OrderGain1 : public OrderGain<1> // these simply just act as wrappers of OrderGain to chuck
{
public:
	OrderGain1(t_CKFLOAT fs) {};
};

class OrderGain2 : public OrderGain<2>
{
public:
	OrderGain2(t_CKFLOAT fs) {};
};

class OrderGain3 : public OrderGain<3>
{
public:
	OrderGain3(t_CKFLOAT fs) {};
};

class OrderGain4 : public OrderGain<4>
{
public:
	OrderGain4(t_CKFLOAT fs) {};
};

class OrderGain5 : public OrderGain<5>
{
public:
	OrderGain5(t_CKFLOAT fs) {};
};

#endif
