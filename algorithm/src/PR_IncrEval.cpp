#include "PR_IncrEval.h"

void PR_IncrEval::IncrEval_Init(GQAP& _probObj) {
	_problem = & _probObj;
}

PR_IncrEval::PR_IncrEval() {
}

void PR_IncrEval::operator ()(PR_Neighbor::EOT& _solution, GQAP_Solution _neighbor, int idx) {
	// Calculates the Increase in the Objective function
	
	double incrTotal = 0;
	incrTotal = CalculateIncrCosts(idx, _solution[idx], _neighbor.solution[idx], _problem);
	
	// Update fitness value
	_neighbor.fitness(_solution.fitness() + incrTotal);
}
