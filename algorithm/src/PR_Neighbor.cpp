#include "PR_Neighbor.h"


void PR_Neighbor::translate(unsigned int _key, GQAP& _solution, GQAP_Solution sol_target) {
	// This function translates a given key from the interval [0, NeighborhoodSize) to a corresponding
	// new assignment. The neighborhood size is equal to the equipment and moves are always made from the
	// starting solution to the target solution
	
	equipment = _key;
	newLocation = sol_target[equipment];
}

void PR_Neighbor::move(GQAP& _solution, GQAP_Solution sol_target) {
	// make the move on the current problem
	translate(key, _solution, sol_target);
	
	_solution.solution[equipment] = newLocation;
	_solution.CalculateCapacityViolations();
	_solution.fitness(this->fitness());
}

void PR_Neighbor::move(GQAP& _solution) {
	throw std::runtime_error("ERROR: Must not call PR_Neighbor::move without a target solution");
}

void PR_Neighbor::getMove(int& _equipment, int& _newLocation, GQAP& _solution, GQAP_Solution sol_target) {
	// Get move ist called by the incremental evaluation function and return
	// the move that will be made in the move function
	
	translate(key, _solution, sol_target);
	_equipment = equipment;
	_newLocation = newLocation;
}

unsigned int PR_Neighbor::getKey() {
	return key;
}
