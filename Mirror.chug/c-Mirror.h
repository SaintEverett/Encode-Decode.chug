//---------------------------------------------------------
//
//		name: c-Mirror.h
//			author: everett m. carpenter
//		
//		desc: helper class to create diag matrices for 
//			  ambisonic transformations. matrices created
//			  by calling .mode(int) where 
//			
//			  mode 0 - reflect (flip) up and down
//			  mode 1 - reflect left and right
//			  mode 2 - reflect front and back
// 
//			  applying these transformations is done by 
//			  multiplying the resulting array by incoming 
//			  BFormat signals. indexed using ACN, thus: 
//
// 			  mirrorValues[ACN] * bformat[ACN] = ~bformat;
//			
//---------------------------------------------------------

#include <cmath>

class Mirror
{
public:
	Mirror(float fs) {};
	~Mirror() {};

	void mode(int m)
	{
		switch (m)
		{
		case 0:
			for (int i = 0; i < (sizeof(mirrorValues) / sizeof(mirrorValues[0])); i++)
			{
				int n = (floor(sqrt(i)));
				int m = (i - (n * n) - n);
				mirrorValues[i] = pow(-1, n + m);
			}
		case 1:
			for (int i = 0; i < (sizeof(mirrorValues) / sizeof(mirrorValues[0])); i++)
			{
				int n = (floor(sqrt(i)));
				int m = (i - (n * n) - n);
				if (m < 0) mirrorValues[i] = -1;
				else mirrorValues[i] = 1;
			}
		case 2:
			for (int i = 0; i < (sizeof(mirrorValues) / sizeof(mirrorValues[0])); i++)
			{
				int n = (floor(sqrt(i)));
				int m = (i - (n * n) - n);
				if (m < 0) mirrorValues[i] = pow(-1, (m + 1));
				else mirrorValues[i] = pow(-1, m);
			}
		}
	}

	int* getMirror()
	{
		return mirrorValues;
	}

private:
	int mirrorValues[36] = { 0 };
};