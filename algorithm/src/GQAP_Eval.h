#ifndef GQAP_EVAL_H
#define GQAP_EVAL_H

#include "GQAP.h"
#include <eoEvalFunc.h>

// defines the full evaluation function for the GQAP in 
// a seperate class to use in build-in heuristics
class GQAP_Eval : public eoEvalFunc <GQAP> {
public:
	void operator() (GQAP & _problem) {
		_problem.fullEvaluation();
	}
};

#endif // GQAP_EVAL_H
