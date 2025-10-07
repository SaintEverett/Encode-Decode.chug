/*----------------------------------------------------------------------------
  ChucK Strongly-timed Audio Programming Language
    Compiler and Virtual Machine

  Copyright (c) 2003 Ge Wang and Perry R. Cook. All rights reserved.
    http://chuck.stanford.edu/
    http://chuck.cs.princeton.edu/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  U.S.A.
-----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
* 
* Encode.chug header file
* 
-----------------------------------------------------------------------------*/
#include "chugin.h"
#include <limits.h>
//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
template<unsigned n_order>
class Encoder
{
public:
    Encoder() 
    {   
        channel_matrix.resize(channel_count);
        temp_matrix.resize(channel_count);
    };
    // for chugins extending UGen
    void tick(SAMPLE* in, SAMPLE* out, int nframes)
    {
        for (int f = 0; f < nframes; f++)
        {
            zeroCrossing = abs(in[f]) < ZERO_THRESHOLD ? TRUE : FALSE; //  less that threshold? zeroCrossing TRUE else FALSE
        }

        if (zeroCrossing && channel_matrix != temp_matrix) // zero crossing and matrices aren't the same?
        {
            for (int i = 0; i < channel_count; i++)
            {
                channel_matrix[i] = temp_matrix[i]; // swap it out
            }
        }

        memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear

        for (int f = 0; f < nframes; f++)
        {
            for (int i = 0; i < channel_count; i++)
            {
                out[f * channel_count + i] = (in[f] * channel_matrix[i]); // in stream is mono so frame is channel 0
            }
        }

    }

    void set_coefficients(Chuck_ArrayFloat* coord, CK_DL_API API)
    {
        int size = (API->object->array_float_size(coord));
        if (size >= channel_count)
        {
            for (int i = 0; i < size;i++)
            {
                temp_matrix[i] = (API->object->array_float_get_idx(coord, i));
            }
        }
    }

    t_CKFLOAT get_i(t_CKUINT index)
    {
        if (index < channel_count) { return channel_matrix[index]; }
        else return NULL;
    }

    void set_i(t_CKFLOAT value, t_CKUINT index)
    {
        if (index < channel_count)
        {
            temp_matrix[index] = value;
        }
        else NULL;
    }

    void position(t_CKFLOAT azimuth_, t_CKFLOAT zenith_)
    {
        temp_matrix = SH(order, azimuth_, zenith_, 0); // simply just calls the spherical harmonic calculator
    }

    std::vector<float> getSH()
    {
        std::vector<float> store;
        store.resize(channel_count);
        for (int i = 0; i < temp_matrix.size(); i++)
        {
            store[i] = temp_matrix[i];
        }
        return store;
    }

public:
    // instance data
    constexpr static unsigned order = n_order;
    constexpr static unsigned channel_count = (n_order + 1) * (n_order + 1);
    std::vector<float> channel_matrix; // current gain coeffs
    std::vector<float> temp_matrix; // temp coeffs to be shifted to current
    bool zeroCrossing = FALSE; // is there a zero crossing?
};