#ifndef MMADN_H
#define MMADN_H

#include "DecoderBase.h"


template<unsigned m_order>
class MMAD : public Decoder<m_order>
{
	MMAD() {};
	~MMAD() {};

	std::array<std::array<float, n_channels>, n_channels> transposeSH(std::array<std::array<float, n_channels>, n_channels> matrix) // this is incredibly ugly
	{
		std::array<std::array<float, n_channels>, n_channels> output = { 0 };
		for (int i = 0; i < n_channels; i++)
		{
			for (int j = 0; j < n_channels; j++)
			{
				output[i][j] = matrix[j][i];
			}
		}
		return output;
	}

public:

};

#endif /* MMADN_H */