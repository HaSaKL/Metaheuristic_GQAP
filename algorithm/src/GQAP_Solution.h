#ifndef GQAP_SOLUTION_H
#define GQAP_SOLUTION_H

#include <eo>

// Base class for GQAP Problems. Only contains the 
// representation of the problem solution and is used for 
// saving different solutions. No additional problem data.

class GQAP_Solution : public EO<eoMinimizingFitness>
{
public:
	// Representation of a solution
	eoVector<eoMinimizingFitness, int> solution;
};

#endif // GQAP_SOLUTION_H
