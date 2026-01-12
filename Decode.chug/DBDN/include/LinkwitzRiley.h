#ifndef BIQUAD_H
#define BIQUAD_H

#ifndef SAMPLE
#define SAMPLE float
#endif /* SAMPLE */

#ifndef pi
#define pi 3.141592653589793
#endif

#include <cmath>

class LinkwitzRiley
{
public:
	LinkwitzRiley() { s_rate = 0; };
	LinkwitzRiley(float fc, float fs)
	{
		s_rate = fs;
		cf = fc;
		highpassCoeff(fc, fs);
		lowpassCoeff(fc, fs);
	}

	SAMPLE htick(SAMPLE in) // direct form II taken from https://www.musicdsp.org/en/latest/Filters/275-direct-form-ii-biquad.html
	{
		in_0 = in; 
		hz_0 = hb_0 * in_0 + hb_1 * in_1 + hb_2 * in_2;
		hz_0 -= a_2 * hz_2 + a_1 * hz_1;
		in_2 = in_1;
		in_1 = in_0;
		hz_2 = hz_1;
		hz_1 = hz_0;
		return hz_0;
	}

	SAMPLE ltick(SAMPLE in)
	{
		in_0 = in;  // a_0 is now 1.0, so just in
		lz_0 = lb_0 * in_0 + lb_1 * in_1 + lb_2 * in_2;
		lz_0 -= a_2 * lz_2 + a_1 * lz_1;
		in_2 = in_1;
		in_1 = in_0;
		lz_2 = lz_1;
		lz_1 = lz_0;
		return lz_0;
	}

	void highpassCoeff(float fc, float fs)
	{
		float Q = 0.707f;
		float omega = 2.f * pi * (fc / fs);
		float alpha = sinf(omega) / (2.f * Q);

		hb_0 = (1.f + cosf(omega)) / 2.f;
		hb_1 = -(1.f + cosf(omega));
		hb_2 = hb_0;

		a_0 = 1.f + alpha;
		a_1 = -2.f * cos(omega);
		a_2 = 1.f - alpha;

		// normalize by a0
		hb_0 /= a_0;
		hb_1 /= a_0;
		hb_2 /= a_0;
		a_1 /= a_0;
		a_2 /= a_0;
		a_0 = 1.0f;
	}

	void lowpassCoeff(float fc, float fs)
	{
		float Q = 0.707f; 
		float omega = 2.f * pi * (fc / fs);
		float alpha = sinf(omega) / (2.f * Q);
		float cosw = cosf(omega);

		lb_0 = (1.f - cosw) / 2.f;
		lb_1 = (1.f - cosw); 
		lb_2 = lb_0;

		// normalize by a0
		float norm = 1.f / a_0;
		lb_0 *= norm;
		lb_1 *= norm;
		lb_2 *= norm;
		a_1 *= norm;
		a_2 *= norm;
		a_0 = 1.0f;
	}

protected:
	float s_rate;
	float cf = 0;
	// a coeffs
	float a_0 = 0;
	float a_1 = 0;
	float a_2 = 0;
	// hi coeffs
	float hb_0 = 0;
	float hb_1 = 0;
	float hb_2 = 0;
	// lo coeffs
	float lb_0 = 0;
	float lb_1 = 0;
	float lb_2 = 0;
	// in delay
	SAMPLE in_0 = 0;
	SAMPLE in_1 = 0;
	SAMPLE in_2 = 0;
	// hi state
	SAMPLE hz_0 = 0;
	SAMPLE hz_1 = 0;
	SAMPLE hz_2 = 0;
	// lo state
	SAMPLE lz_0 = 0;
	SAMPLE lz_1 = 0;
	SAMPLE lz_2 = 0;
};

#endif