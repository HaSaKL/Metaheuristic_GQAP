#ifndef GRASP_UNIFORMRANDOMALPHA_H
#define GRASP_UNIFORMRANDOMALPHA_H

#include "GRASP_Alpha.h"
#include <utils/eoRNG.h> // for random numbers
#include "GQAP.h"

// Class which returns a random alpha value
class GRASP_UniformRandomAlpha: public GRASP_Alpha
{
private:
	double minAlpha;
	double numAlpha;
	double stepAlpha;
	
public:
	GRASP_UniformRandomAlpha(double _maxAlpha, double _minAlpha, int _numAlpha);
	void init(GQAP & _p);
	double operator() (GQAP & _p);

};

#endif // GRASP_UNIFORMRANDOMALPHA_H
