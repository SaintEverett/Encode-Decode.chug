#include "math.h"

#define R_PI 3.141592653589793

class CrossoverFilter
{
	CrossoverFilter::CrossoverFilter(float cutoff, unsigned fs)
	{
		float m_fs = fs;
		float k = tanf((cutoff * R_PI) / m_fs);
	}
};
