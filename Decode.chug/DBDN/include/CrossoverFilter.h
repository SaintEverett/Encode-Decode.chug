#include <cmath>
#include <array>

#define R_PI 3.141592653589793

void shift(std::array<float, 4> sort)
{
	for (int i = (sort.size()-1); i > 0; i--)
	{
		sort[i] = sort[i - 1];
	}
}

class CrossoverFilter
{
public:
	CrossoverFilter(float cutoff, float fs)
	{
		s_rate = fs;
		cross = cutoff;
		k = tanf((cross * R_PI) / s_rate);
		float ks = k * k;
		float d = 1.0f / (ks + k * std::sqrt(2.0f) + 1.0f);
		// lo
		lf_b[0] = ks * d;
		lf_b[1] = 2.0f * lf_b[0];
		lf_b[2] = lf_b[0];
		// hi
		hf_b[0] = 1.0f * d;
		hf_b[1] = -2.0f * hf_b[0];
		hf_b[2] = hf_b[0];
		a[1] = 2.0f * (ks - 1.0f) * d;
		a[2] = (ks - k * std::sqrt(2.0f) + 1.0f) * d;
	}

	void fick(float* in, float* lf_out, float* hf_out)
	{
		float x0 = *in - a[1] * x[1] - a[2] * x[2];

		x[0] = *in; // set x[n]

		// lout
		*lf_out = lf_b[0] * x0 + lf_b[1] * x[1] + lf_b[2] * x[2];
		// hout
		*hf_out = hf_b[0] * x0 + hf_b[1] * x[1] + hf_b[2] * x[2];

		//shift 
		x[2] = x[1];
		x[1] = x0;
	}

private:
	float s_rate;
	float cross;
	float k;
	std::array<float, 4> x{};
	std::array<float, 4> lf_y{};
	std::array<float, 4> hf_y{};
	std::array<float, 4> lf_b{};
	std::array<float, 4> hf_b{};
	std::array<float, 4> a{};
};
