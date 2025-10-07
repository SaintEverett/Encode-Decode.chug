// Decoder base class for inheritance 
#ifndef DECODE_BASE_H
#define DECODE_BASE_H

#include "chugin.h"

template<const unsigned order_>
class Decoder
{
public:
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

	void setSpeakerSH(std::vector<float> n_SpeakSH, unsigned which)
	{
		for (int i = 0; i < n_SpeakSH.size(); i++)
		{
			SpeakSH[which][i] = n_SpeakSH[i];
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

	void CKsetSpeakAngles(Chuck_Object* coord, CK_DL_API API)
	{
		Chuck_ArrayInt* column = (Chuck_ArrayInt*)coord;
		if (API->object->array_int_size(column) == n_channels)
		{
			for (t_CKINT i = 0; i < API->object->array_int_size(column); i++)
			{
				Chuck_ArrayFloat* row = (Chuck_ArrayFloat*)API->object->array_int_get_idx(column, i);
				t_CKUINT size = API->object->array_float_size(row);
				if (size == 2)
				{
					std::vector<float> temp = SH(order, API->object->array_float_get_idx(row, 0), API->object->array_float_get_idx(row, 1), 0);
					setSpeakerSH(temp, i);
				}
			}
		}
	}

protected:
	static constexpr unsigned order = order_; // order
	static constexpr unsigned n_channels = (order_ + 1) * (order_ + 1); // how many channels
	std::array<std::array<float, n_channels>, n_channels> SpeakSH{};
};

#endif /* DECODE_BASEH */