#include "PR_IncrEval.h"

void PR_IncrEval::IncrEval_Init(GQAP _probObj) {
	_problem = & _probObj;
}

PR_IncrEval::PR_IncrEval() {
}

void PR_IncrEval::DoIncrEval(PR_Neighbor::EOT & _solution, PR_Neighbor & _neighbor, GQAP_Solution sol_target) {
	// Calculates the Increase in the Objective function
	
	int equipment;
	int newLocation;
	int oldLocation;
	
	_neighbor.getMove(equipment, newLocation, _solution, sol_target);
	oldLocation = _problem -> solution[equipment];
	
	double incrTotal = 0;
	
	/*//DEBUG
	std::cout << "DEBUG: CalcualtingIncrCosts " << std::endl;
	std::cout << "Equipment: " << equipment << std::endl;
	std::cout << "new Location: " << newLocation << std::endl;
	std::cout << "old Location: " << oldLocation << std::endl;
	//*/
	
	incrTotal = CalculateIncrCosts(equipment, newLocation, oldLocation, _problem);
	
	//std::cout << "DEBUG: Updateing Fitness " << std::endl;
	
	// Update fitness value
	_neighbor.fitness(_solution.fitness() + incrTotal);
}

void PR_IncrEval::operator() (PR_Neighbor::EOT & _solution, PR_Neighbor & _neighbor) {
	throw std::runtime_error("ERROR: Called operator() on PR_IncrEval without providing a targerting solution!");
}