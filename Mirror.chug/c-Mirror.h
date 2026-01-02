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
	Mirror(float fs) { mode(0); };
	Mirror(float fs, int initmode) { mode(initmode); }
	~Mirror() { delete[] mirrorValues; delete& lastMode; };

	void mode(int m)
	{
		if (m != lastMode) haveChanged = 1;
		lastMode = m; // save for later reference
		switch (m)
		{
		case 0:
			for (int i = 0; i < (sizeof(mirrorValues) / sizeof(mirrorValues[0])); i++) // flip up to down and down to up
			{
				int n = (floor(sqrt(i)));
				int m = (i - (n * n) - n);
				mirrorValues[i] = pow(-1, n + m);
			}
			break;
		case 1:
			for (int i = 0; i < (sizeof(mirrorValues) / sizeof(mirrorValues[0])); i++) // flip left to right and right to left
			{
				int n = (floor(sqrt(i)));
				int m = (i - (n * n) - n);
				if (m < 0) mirrorValues[i] = -1;
				else mirrorValues[i] = 1;
			}
			break;
		case 2:
			for (int i = 0; i < (sizeof(mirrorValues) / sizeof(mirrorValues[0])); i++) // flip front to back and back to front
			{
				int n = (floor(sqrt(i)));
				int m = (i - (n * n) - n);
				if (m < 0) mirrorValues[i] = pow(-1, (m + 1));
				else mirrorValues[i] = pow(-1, m);
			}
			break;
		default:
			mode(0);
		}
	}

	int* getMirror()
	{
		return mirrorValues; // return array of values
		haveChanged = 0; // we've called them and have the most recent values
	}

public:
	int mirrorValues[36] = { 0 }; // where we store our "diag" matrix (more so a vector at this point)
	int lastMode = 0; // last used mode (defaults to 0 if no constructor arg is used)
	bool haveChanged = 0; // have they changed since we last called getMirror()?
};