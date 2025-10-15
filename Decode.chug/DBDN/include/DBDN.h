#include "DecoderBase.h"
#include "LinkwitzRiley.h"

template<unsigned order_>
class DBDN : public Decoder<order_>, public LinkwitzRiley
{
public:
	DBDN(float fs) : LinkwitzRiley(1500.f, fs) {};
	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++) // go through each frame
		{
			float highblock[n_channels] = { 0.f };
			float lowblock[n_channels] = { 0.f };
			for (int j = 0; j < n_channels; j++)
			{
				highblock[j] = htick(in[f * n_channels + j]);
				lowblock[j] = ltick(in[f * n_channels + j]);
			}
			for(int c = 0; c < n_channels; c++) // go through each output channel
			{
				SAMPLE sum_high = 0;
				SAMPLE sum_low = 0;
				for (int n = 0; n < n_channels; n++) // sum over input channels
				{
					sum_high += highblock[n] * SpeakSH[c][n];
					sum_low += lowblock[n] * SpeakSH[c][n];
				}
				// Combine with the 0.866 scaling factor for high frequencies
				out[f * n_channels + c] = channelBalance * (0.86602540f * sum_high + sum_low);
			}
		}
	}
};
