#include "PR_Neighbor.h"


void PR_Neighbor::translate(unsigned int _key, GQAP_Solution sol_target, GQAP_Solution sol_start) {
	// This function translates a given key from the interval [0, NeighborhoodSize) to a corresponding
	// new assignment. The neighborhood size is equal to the equipment and moves are always made from the
	// starting solution to the target solution
	
	equipment = _key;
	newLocation = sol_target[equipment];
}

void PR_Neighbor::move(GQAP_Solution sol_target, GQAP& _solution) {
	// make the move on the current problem
	translate(key, sol_target, _solution);
	
	_solution.solution[equipment] = newLocation;
	_solution.CalculateCapacityViolations();
	_solution.fitness(this->fitness());
}

void PR_Neighbor::getMove(int& _equipment, int& _newLocation, GQAP_Solution sol_target, GQAP& _solution) {
	// Get move ist called by the incremental evaluation function and return
	// the move that will be made in the move function
	
	translate(key, sol_target, _solution);
	
	_equipment = equipment;
	_newLocation = newLocation;
}
