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
* Decode.chug header file
*
* psuedoInverse input [SH0(speak1), SH1(speak1), .... SHN(speakN)]
*                     [SH0(speak2), ......                       ]
*                     [SH0(speak3), ......                       ]
*                     [SH0(speak4), ......                       ]
* 
-----------------------------------------------------------------------------*/

#include <Eigen/Core>
#include <Eigen/SVD> 
#include <vector>

std::vector<std::vector<float>> psuedoInverse(std::vector<std::vector<float>> SH)
{
    unsigned numspeak = SH.size();
    unsigned numSH = SH[0].size();
    Eigen::MatrixXf M_e(numSH, numspeak);
    for (int i = 0; i < numspeak; i++)
    {
        for (int j = 0; j < numSH; j++)
        {
            M_e(j, i) = SH[i][j];
        }
    }
    Eigen::JacobiSVD<Eigen::MatrixXf> svd(M_e, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::MatrixXf M_d = svd.matrixV() * svd.singularValues().asDiagonal().inverse() * svd.matrixU().transpose();
    std::vector<std::vector<float>> gains(numSH, std::vector<float>(numspeak));
    for (int i = 0; i < numspeak; i++)
    {
        for (int j = 0; j < numSH; j++)
        {
            M_e(j, i) = SH[j][i];
        }
    }
    return gains;
}