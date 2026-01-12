#include "DecoderBase.h"
#include "LinkwitzRiley.h"

template <unsigned order_>
class DBDN : public Decoder<order_>
{
public:
	DBDN(float fs)
	{
		// Initialize filters array using the base class n_channels
		filters = new LinkwitzRiley[this->n_channels];
		for (int i = 0; i < this->n_channels; i++) 
		{
			filters[i] = LinkwitzRiley(700.f, fs);
		}
		highend = new SAMPLE[this->n_channels];
		lowend = new SAMPLE[this->n_channels];
	}
	~DBDN()
	{
		delete[] filters;
		filters = nullptr;
		delete[] highend;
		highend = nullptr;
		delete[] lowend;
		lowend = nullptr;
	}

	void tick(SAMPLE *in, SAMPLE *out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * this->n_channels * nframes); // clear
		memset(highend, 0, sizeof(SAMPLE) * this->n_channels * nframes); // store filtered blocks
		memset(lowend, 0, sizeof(SAMPLE) * this->n_channels * nframes);
		for (int f = 0; f < nframes; f++)
		{
			for (int c = 0; c < this->n_channels; c++) // filter the entire input buffer
			{
				highend[f * this->n_channels + c] = filters[c].htick(in[f * this->n_channels + c]);
				lowend[f * this->n_channels + c] = filters[c].ltick(in[f * this->n_channels + c]);
			}
		}

		for (int f = 0; f < nframes; f++)
		{
			for (int c = 0; c < this->n_channels; c++)
			{
				SAMPLE summation = 0.0;
				for (int n = 0; n < this->n_channels; n++)
				{
					// summation += ((0.86602540f * highend[f * this->n_channels + n]) + lowend[f * this->n_channels + n]) * SpeakSH[c][n]; // multiply the nth input signal by the cth speaker's nth spherical harmonic and summate them all
					summation += ((0.86602540f * highend[f * this->n_channels + n]) + lowend[f * this->n_channels + n]) * SpeakSH[c][n];
				}
				out[f * this->n_channels + c] = summation;
			}
		}
	}
private:
	LinkwitzRiley* filters;
	SAMPLE* highend;
	SAMPLE* lowend;
};
