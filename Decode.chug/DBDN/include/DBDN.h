#include "DecoderBase.h"
#include "LinkwitzRiley.h"

template<unsigned order_>
class DBDN : public Decoder<order_>, public LinkwitzRiley
{
public:
	DBDN(float fs) : LinkwitzRiley(1500.f, fs) {};
	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		float* h_filtin = nullptr;
		float* l_filtin = nullptr;
		memset(out, 0, sizeof(SAMPLE) * n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++) // go through each frame
		{
			memset(h_filtin, 0, sizeof(SAMPLE) * n_channels); // only need to filter the input once per frame
			memset(l_filtin, 0, sizeof(SAMPLE) * n_channels); 
			for (int j = 0; j < n_channels; j++)
			{
				h_filtin[j] = htick(in[f * n_channels + j]);
				l_filtin[j] = ltick(in[f * n_channels + j]);
			}
			for (int c = 0; c < n_channels; c++) // go through each channel
			{
				SAMPLE sumd = 0;
				for (int n = 0; n < n_channels; n++)
				{
					sumd += h_filtin[n] * 0.86602540f * SpeakSH[c][n];
					sumd += l_filtin[n] * SpeakSH[c][n];
				}
				out[f * n_channels + c] = channelBalance * sumd;
			}
		}
	}
};
