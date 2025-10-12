#include "DecoderBase.h"
#include "CrossoverFilter.h"

template<unsigned order_>
class DBDN : public Decoder<order_>, public CrossoverFilter
{
public:
	DBDN(float fs) : CrossoverFilter(1500.f, fs) {};
	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++) // go through each frame
		{
			for (int c = 0; c < n_channels; c++) // go through each channel
			{
				SAMPLE sumd = 0;
				for (int n = 0; n < n_channels; n++) // each channel of the incoming stream is a spherical harmonic
				{
					fick(&in[f * n_channels + n], &lo, &hi); // split it into two bands
					sumd += (0.5 * lo * SpeakSH[c][n]); // matrix mult of speaker SHs and input stream
					sumd += (0.5 * hi * 0.8660254037844386 * SpeakSH[c][n]); // matrix mult of speaker SHs and input stream
				}
				out[f * n_channels + c] = sumd;
			}
		}
	}


public:
	SAMPLE hi;
	SAMPLE lo;
};
