#ifndef SADN_H
#define SADN_H

template<const unsigned order_>
class SADN
{
public:
	
	constexpr void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++)
		{
			SAMPLE sumd = 0;
			for (int c = 0; c < n_channels; c++)
			{
				for (int n = 0; n < n_channels; n++)
				{
					sumd += in[f * n_channels + c] * SpeakSH[c][n]; // matrix mult of speaker SHs and input stream
				}
				out[f * n_channels + c] = sumd;
			}
		}
	}

	void setSpeakerSH(std::vector<std::vector<float>> n_SpeakSH)
	{
		for (int i = 0; i < n_channels; i++)
		{
			for (int j = 0; j < n_channels; j++)
			{
				SpeakSH[i][j] = n_SpeakSH[i][j];
			}
		}
	}

	std::vector<std::vector<float>> getSpeakerSH()
	{
		std::vector<std::vector<float>> store;
		store.resize(n_channels);
		for (int i = 0; i < SpeakSH.size(); i++)
		{
			store[i].resize(n_channels);
			for (int j = 0; j < SpeakSH[i].size(); j++)
			{
				store[i][j] = SpeakSH[i][j];
			}
		}
		return store;
	}

protected:
	static constexpr unsigned order = order_; // order
	static constexpr unsigned n_channels = (order_ + 1) * (order_ + 1); // how many channels
	std::array<std::array<float, n_channels>, n_channels> SpeakSH{};
};

#endif /* SADN_H */