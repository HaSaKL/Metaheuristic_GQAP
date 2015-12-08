#include "GQAP_ElementFlip_IncrEval.h"

// Constructor
GQAP_ElementFlip_IncrEval::GQAP_ElementFlip_IncrEval(GQAP & _probObj) {
	_problem = & _probObj;
}
	
// Interface function
void GQAP_ElementFlip_IncrEval::operator() (GQAP_ElementFlipIndex_Neighbor::EOT & _solution, GQAP_ElementFlipIndex_Neighbor & _neighbor) {
	// Calculate Increased Costs and Update Fitness Value
	
	// get indices of changes assignment
	int equipment;
	int newLocation;
	int oldLocation;
	
	_neighbor.getMove(equipment, newLocation, _solution);
	oldLocation = _problem -> solution[equipment];
	
	// Calculate Cost Increase
	double incrTotal = 0;
	incrTotal = CalculateIncrCosts(equipment, newLocation, oldLocation, _problem);
	
	/*// DEBUG OUTPUT
	std::cout << "Move Equipment " << equipment << " from location " << oldLocation << " to " << newLocation << std::endl;
	std::cout << "Old Solution Value: " << _solution.fitness() << std::endl;
	std::cout << "Increase:           " << incrTotal << std::endl;
	std::cout << "New Solution Value: " << _solution.fitness() + incrTotal << std::endl << std::endl;
	// */
	
	// Set new Costs
	_neighbor.fitness(_solution.fitness() + incrTotal);
}