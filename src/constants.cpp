


#include "constants.h"







bool numbers_are_the_same(double d1, double d2)
{
	if (d1 == d2)
		return true;
	
	if (d1 < d2)
	{
		return d2 - d1 < 1e-5;
	}
	else
	{
		return d1 - d2 < 1e-5;
	}
}