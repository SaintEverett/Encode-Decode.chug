#include <cmath>
#include <vector>

#define R_PI 3.141592653589793

class CrossoverFilter
{
public:
	CrossoverFilter(float cutoff, unsigned fs)
	{
		srate = fs;
		cross = cutoff;
		k = tanf((cross * R_PI) / srate);
		x = std::vector<float>(3, 0.0f);
		y = std::vector<float>(3, 0.0f);
		float ks = pow(k, 2);
		float d = (ks + (2.0 * k) + 1);
		b_lf = {(ks / d), (2.f * (ks / d)), (ks / d)};
		b_hf = {(1.f / d), (-2.f * (1.f / d)), (1.f / d)};
		a = {1.f, ((2.f * (ks - 1.f)) / d), ((ks - (2.f * k) + 1.f) / d)};
	}

	CrossoverFilter(float cutoff, float fs)
	{
		srate = fs;
		cross = cutoff;
		k = tanf((cross * R_PI) / srate);
		x = std::vector<float>(3, 0.0f);
		y = std::vector<float>(3, 0.0f);
		float ks = pow(k, 2);
		float d = (ks + (2.f * k) + 1.f);
		b_lf = { (ks / d), (2.f * (ks / d)), (ks / d) };
		b_hf = { (1.f / d), (-2.f * (1.f / d)), (1.f / d) };
		a = { 1.f, ((2.f * (ks - 1.f)) / d), ((ks - (2.f * k) + 1.f) / d) };
	}

	void tick(float* in, float* out)
	{
		y[0] = b_lf[0] * (*in) + b_lf[1] * x[1] + b_lf[2] * x[2] - a[1] * y[1] - a[2] * y[2];	
		*out = y[0];
		// shift x
		x[1] = *in;
		x[2] = x[1];
		// shift y
		y[2] = y[1];
		y[1] = y[0];
	}

private:
	float srate;
	float cross;
	float k;
	std::vector<float> x;
	std::vector<float> y;
	std::vector<float> b_lf;
	std::vector<float> b_hf;
	std::vector<float> a;
};
