#ifndef GRASP_FIXEDALPHA_H
#define GRASP_FIXEDALPHA_H

#include "GRASP_Alpha.h"
#include "GQAP.h"

// Class which always returns a fixed alpha value
class GRASP_FixedAlpha: public GRASP_Alpha
{
private:
	double alpha;
	
public:
	GRASP_FixedAlpha(double _alpha);
	void init();
	void init(GQAP & _p);
	double operator() (GQAP & _p);
};

#endif // GRASP_FIXEDALPHA_H
