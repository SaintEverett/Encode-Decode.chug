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
		for (unsigned i = 0; i < this->n_channels; i++) 
		{
			filters[i] = LinkwitzRiley(700.f, fs);
		}
		highblock = new SAMPLE[this->n_channels];
		lowblock = new SAMPLE[this->n_channels];
	}
	~DBDN()
	{
		delete[] filters;
		delete[] highblock;
		delete[] lowblock;
	}

	void tick(SAMPLE *in, SAMPLE *out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * this->n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++)							 // go through each frame
		{
			memset(highblock, 0, sizeof(SAMPLE) * this->n_channels * nframes);
			memset(lowblock, 0, sizeof(SAMPLE) * this->n_channels * nframes);
			for (int j = 0; j < this->n_channels; j++)
			{
				highblock[j] = filters[j].htick(in[f * this->n_channels + j]);
				lowblock[j] = filters[j].ltick(in[f * this->n_channels + j]);
			}
			for (int c = 0; c < this->n_channels; c++) // go through each output channel
			{
				SAMPLE sum_high = 0.f;
				SAMPLE sum_low = 0.f;
				for (int n = 0; n < this->n_channels; n++) // sum over input channels
				{
					sum_high += highblock[n] * this->SpeakSH[c][n];
					sum_low += lowblock[n] * this->SpeakSH[c][n];
				}
				// Combine with the 0.866 scaling factor for high frequencies
				//out[f * this->n_channels + c] = this->channelBalance * ((0.86602540f * sum_high) + sum_low);
				out[f * this->n_channels + c] = this->channelBalance * (0.86602540f * sum_high);
			}
		}
	}
private:
	LinkwitzRiley* filters;
	SAMPLE* highblock;
	SAMPLE* lowblock;
};
