#ifndef GRASP_ALPHA_H
#define GRASP_ALPHA_H

#include "GQAP.h"

// Abstract base class for all alpha-related classes
class GRASP_Alpha
{
public:
	virtual double operator() (GQAP & _p)= 0;
	virtual void init(GQAP & _p) = 0;
};

#endif // GRASP_ALPHA_H
