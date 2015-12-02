#include "GQAP_ElementFlip_Neighbor.h"

void GQAP_ElementFlipIndex_Neighbor::move(GQAP& _solution) {
	// make the move
	
	// translate index key to a specific move
	translate(key, _solution);
	
	/*// DEBUG
	std::cout << "Current Solution: ";
	_solution.printSolution();
	//*/
	
	// execute this move
	_solution.solution[EquipmentToLocation.first] = EquipmentToLocation.second;
	_solution.CalculateCapacityViolations();
	_solution.fitness(this->fitness());
	
	/*// DEBUG
	_solution.fullEvaluation();
	if (_solution.fitness() != this->fitness()) {
		std::cout << "New Solution:     ";
		_solution.printSolution();
		
		_solution.printFitness();
		std::cout << "vs. " << fitness() << std::endl;
		std::cout << "Delta: " << _solution.fitness() - this->fitness() << std::endl;
		throw std::runtime_error("Error in Incremental Evaluation");
	}
	// */
}

void GQAP_ElementFlipIndex_Neighbor::translate(unsigned int _key, GQAP & _solution) {
	// This function translates a given key from the interval [0, NeighborhoodSize)
	// to a corresponding assignment. The result is saved in the pair EquipmentToLocation,
	// Since there are numLocation-1 possible flips for each Equipment, there are a total of
	// [numEquipment * (numLocation-1)] possible Neighbors
	
	// the are coded this fashion (for 4 Locations)
	//	key-value	operation
	//	0			Equipment 0 -> newLocation = oldLocation + 1
	//	1			Equipment 0 -> newLocation = oldLocation + 2
	// 	2			Equipment 0 -> newLocation = oldLocation + 3
	//	3			Equipment 1 -> newLocation = oldLocation + 1
	// 	4			Equipment 1 -> newLocation = oldLocation + 2
	//	...			...
	
	// The translation uses integer devision with remainder:
	// The interger value results in the Equipment which is moved and 
	// the remainer translates to the index of the moved location ,while 
	// considering a wrap around in the location index (e.g. location 1 + 3
	// yields location 0; wrap around afer location 3 to location 0)
	
	// define struc for dev result from stdlib.
	div_t res;
	
	//since there are numLocations-1 other locations to consider:
	int maxLocationNum = _solution.GetNumLocation() - 1; 
	res = div(_key, maxLocationNum);
	
	// set Equipment index of Move
	EquipmentToLocation.first = res.quot;
	
	// set Location index of Move, while considering wrap-around
	EquipmentToLocation.second = _solution[EquipmentToLocation.first] + res.rem + 1;
	if (EquipmentToLocation.second > maxLocationNum) {
		EquipmentToLocation.second -= maxLocationNum+1;
	}
	
}

void GQAP_ElementFlipIndex_Neighbor::getMove(int & _equipment, int & _newLocation, GQAP & _solution) {
	// Get move is called by the incremental evaluation function and returns
	// the move that hase been made in the move function
	translate(key, _solution);
	_equipment = EquipmentToLocation.first;
	_newLocation = EquipmentToLocation.second;
}