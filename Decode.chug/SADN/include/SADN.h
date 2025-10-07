#ifndef SADN_H
#define SADN_H

template<const unsigned order_>
class SADN
{
public:
	
	constexpr void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++) // go through each frame
		{
			for (int c = 0; c < n_channels; c++) // go through each channel
			{
				SAMPLE sumd = 0;
				for (int n = 0; n < n_channels; n++) // each channel of the incoming stream is a spherical harmonic
				{
					sumd += ((1.f / n_channels) * in[f * n_channels + n] * SpeakSH[c][n]); // matrix mult of speaker SHs and input stream
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

protected:
	static constexpr unsigned order = order_; // order
	static constexpr unsigned n_channels = (order_ + 1) * (order_ + 1); // how many channels
	std::array<std::array<float, n_channels>, n_channels> SpeakSH{};
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD1 : public SADN<1>
{
public:

	SAD1(t_CKFLOAT fs) {};

	void setSpeakersAngles(Chuck_Object* coord, CK_DL_API API)
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

	// set parameter example
	t_CKFLOAT setParam(t_CKFLOAT p)
	{
		m_param = p;
		return p;
	}

	// get parameter example
	t_CKFLOAT getParam() { return m_param; }

private:
	// instance data
	t_CKFLOAT m_param = 0.f;
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD2 : public SADN<2>
{
public:

	SAD2(t_CKFLOAT fs) {};

	void setSpeakersAngles(Chuck_Object* coord, CK_DL_API API)
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

	// set parameter example
	t_CKFLOAT setParam(t_CKFLOAT p)
	{
		m_param = p;
		return p;
	}

	// get parameter example
	t_CKFLOAT getParam() { return m_param; }

private:
	// instance data
	t_CKFLOAT m_param = 0.f;
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD3 : public SADN<3>
{
public:

	SAD3(t_CKFLOAT fs) {};

	void setSpeakersAngles(Chuck_Object* coord, CK_DL_API API)
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

	// set parameter example
	t_CKFLOAT setParam(t_CKFLOAT p)
	{
		m_param = p;
		return p;
	}

	// get parameter example
	t_CKFLOAT getParam() { return m_param; }

private:
	// instance data
	t_CKFLOAT m_param = 0.f;
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD4 : public SADN<4>
{
public:

	SAD4(t_CKFLOAT fs) {};

	void setSpeakersAngles(Chuck_Object* coord, CK_DL_API API)
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

	// set parameter example
	t_CKFLOAT setParam(t_CKFLOAT p)
	{
		m_param = p;
		return p;
	}

	// get parameter example
	t_CKFLOAT getParam() { return m_param; }

private:
	// instance data
	t_CKFLOAT m_param = 0.f;
};

//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
class SAD5 : public SADN<5>
{
public:

	SAD5(t_CKFLOAT fs) {};

	void setSpeakersAngles(Chuck_Object* coord, CK_DL_API API)
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

	// set parameter example
	t_CKFLOAT setParam(t_CKFLOAT p)
	{
		m_param = p;
		return p;
	}

	// get parameter example
	t_CKFLOAT getParam() { return m_param; }

private:
	// instance data
	t_CKFLOAT m_param = 0.f;
};

#endif /* SADN_H */