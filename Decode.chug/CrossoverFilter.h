#include <cmath>
#include <vector>

#define R_PI 3.141592653589793

void shift(std::vector<float> sort)
{
	for (int i = (sort.size()-1); i > 0; i--)
	{
		sort[i] = sort[i - 1];
	}
}

class CrossoverFilter
{
public:
	CrossoverFilter(float cutoff, unsigned fs)
	{
		srate = fs;
		cross = cutoff;
		k = tanf((cross * R_PI) / srate);
		x = std::vector<float>(4, 0.f);
		lf_y = std::vector<float>(4, 0.f);
		hf_y = std::vector<float>(4, 0.f);
		float ks = pow(k, 2);
		float d = (ks + (2.0 * k) + 1);
		lf_b = {(ks / d), (2.f * (ks / d)), (ks / d)};
		hf_b = {(1.f / d), (-2.f * (1.f / d)), (1.f / d)};
		a = {1.f, ((2.f * (ks - 1.f)) / d), ((ks - (2.f * k) + 1.f) / d)};
	}

	void fick(float* in, float* lf_out, float* hf_out)
	{
		shift(lf_y);
		shift(hf_y);
		shift(x);

		x[0] = *in; // set x[n]
		
		// low pass out
		lf_y[0] = ((lf_b[0] * x[0]) + (lf_b[1] * x[1]) + (lf_b[2] * x[2]) - (a[1] * lf_y[1]) - (a[2] * lf_y[2]));
		*lf_out = lf_y[0];

		// high pass out
		hf_y[0] = ((hf_b[0] * x[0]) + (hf_b[1] * x[1]) + (hf_b[2] * x[2]) - (a[1] * hf_y[1]) - (a[2] * hf_y[2]));
		*hf_out = hf_y[0];
	}

private:
	float srate;
	float cross;
	float k;
	std::vector<float> x;
	std::vector<float> lf_y;
	std::vector<float> hf_y;
	std::vector<float> lf_b;
	std::vector<float> hf_b;
	std::vector<float> a;
};
