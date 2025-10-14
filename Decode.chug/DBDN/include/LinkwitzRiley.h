#ifndef BIQUAD_H
#define BIQUAD_H

#ifndef SAMPLE
#define SAMPLE float
#endif /* SAMPLE */

#ifndef pi
#define pi 3.141592653589793
#endif

#include <cmath>

#define dn 1.0e20f

class LinkwitzRiley
{
public:
	LinkwitzRiley(float fc, float fs)
	{
		s_rate = fs;
		cf = fc;
		highpassCoeff(fc, fs);
		lowpassCoeff(fc, fs);
	}

	SAMPLE htick(SAMPLE in) // direct form II taken from https://www.musicdsp.org/en/latest/Filters/275-direct-form-ii-biquad.html
	{
		float w = in - a_1 * hz_1 - a_2 * hz_2 + dn;
		SAMPLE out = hb_0 * hz_1 + hb_1 * hz_2 + hb_0 * w;
		hz_2 = hz_1; // memory shift
		hz_1 = out;
		return out;
	}

	SAMPLE ltick(SAMPLE in)
	{
		float w = in - a_1 * lz_1 - a_2 * lz_2 + dn;
		SAMPLE out = lb_0 * lz_1 + lb_1 * lz_2 + lb_0 * w;
		lz_2 = lz_1; // memory shift
		lz_1 = out;
		return out;
	}

	void highpassCoeff(float fc, float fs)
	{
		float Q = 0.707f;
		float omega = 2.f * pi * (fc / fs);
		float alpha = sinf(omega) / (2.f * Q);
		hb_0 = (1.f + cosf(omega)) / 2.f;
		hb_1 = -1.f - cosf(omega);
	}

	void lowpassCoeff(float fc, float fs)
	{
		float Q = 0.707f;
		float omega = 2.f * pi * (fc / fs);
		float alpha = sinf(omega) / (2.f * Q);
		lb_0 = (1.f - cosf(omega)) / 2.f;
		lb_1 = 1.f - cosf(omega);
	}

protected:
	float s_rate;
	float cf;
	// a coeffs
	float a_1 = 0;
	float a_2 = 0;
	// hi coeffs
	float hb_0 = 0;
	float hb_1 = 0;
	// lo coeffs
	float lb_0 = 0;
	float lb_1 = 0;
	// hi state
	SAMPLE hz_1 = 0;
	SAMPLE hz_2 = 0;
	// lo state
	SAMPLE lz_1 = 0;
	SAMPLE lz_2 = 0;
};

#endif