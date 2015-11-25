#ifndef GQAP_ELEMENTFLIP_INCREVAL_H
#define GQAP_ELEMENTFLIP_INCREVAL_H

#include "GQAP.h"
#include "GQAP_ElementFlip_Neighbor.h"
#include <eval/moEval.h>

class GQAP_ElementFlip_IncrEval: public moEval<GQAP_ElementFlipIndex_Neighbor> {
public:

	// Constructor
	GQAP_ElementFlip_IncrEval(GQAP & _probObj);
	
	// Interface function
	void operator() (GQAP_ElementFlipIndex_Neighbor::EOT & _solution, GQAP_ElementFlipIndex_Neighbor & _neighbor);

private:
	GQAP* _problem;	// pointer to Problem to access its parameters and current solution
	double CalculateIncrCosts (int equipment, int newLocation, int oldLocation);
	
};

#endif // GQAP_ELEMENTFLIP_INCREVAL_H