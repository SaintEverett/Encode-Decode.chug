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

bool equalTest(double array1[], double array2[], int size1, int size2)
{
    int largest;
    if (size1 != size2)
    {
        largest = std::min(size1, size2); // smaller one
    }
    else if (size1 == size2)
    {
        largest = size1;
    }
    for (int i = 0; i < largest; i++)
    {
        if (array1[i] != array2[i]) return FALSE;
        else return TRUE;
    }
}
