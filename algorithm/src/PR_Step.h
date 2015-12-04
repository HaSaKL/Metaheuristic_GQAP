#ifndef PATH_RELINKING_STEP_H
#define PATH_RELINKING_STEP_H

#include "GQAP_Solution.h"

// Abstract base class for all path-relinking directions
// StepForware, StepBackwards and StepMixes derive from here.
class PR_Step
{
public:
	virtual GQAP_Solution operator() (GQAP_Solution sol_target, GQAP_Solution sol_start) = 0;
};

#endif // PATH_RELINKING_STEP_H
