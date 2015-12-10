#ifndef PR_INCREMENTAL_EVAL
#define PR_INCREMENTAL_EVAL

#include "GQAP_IncrEval_Base_ElementFlip.h"
#include "GQAP.h"
#include "PR_Neighbor.h"
#include <eval/moEval.h>

class PR_IncrEval: public moEval<PR_Neighbor>, public GQAP_IncrEval_Base_ElementFlip {
	// inherit from GQAP_ElementFlip_IncrEval for the CalculateIncrCosts-function
	// inherit from moEval for the rest
	
public:
	
	// constructor
	PR_IncrEval();
	void IncrEval_Init(GQAP _probObj);
	
	// Interface function
	void DoIncrEval(PR_Neighbor::EOT & _solution, PR_Neighbor & _neighbor, GQAP_Solution sol_target);
	void operator() (PR_Neighbor::EOT & _solution, PR_Neighbor & _neighbor);
	
	// pointer to problem to access its parameters and current solution, could also be realized using friends!
	GQAP* _problem;
};

#endif // PR_INCREMENTAL_EVAL
