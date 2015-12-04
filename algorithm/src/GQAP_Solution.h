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
	
	void printFitness() {
		if (!invalid()) {
			std::cout << "Fitness: " << fitness() << std::endl;
		} else {
			std::cout << "Fitness is invalid. Did you Evaluate the Fitness?" << std::endl;
		}
	}

	void printSolution() {
		std::cout << "Solution: ";
		for (int i = 0; i < solution.size()-1; i++) {
			std::cout << solution[i] << " ; ";
		}
		std::cout << solution.back() << std::endl;
	}
	
	bool operator== (const GQAP_Solution sol_ref) { 
		// returns true if sol1 and sol2 are equal
		
		if (solution.size() != sol_ref.solution.size()) {
			return false;
		} 
		
		for(int i = 0; i < solution.size(); i++) {
			if (solution[i] != sol_ref.solution[i]) {
				return false;
			}
		}
		
		return true;
	}
	
};

#endif // GQAP_SOLUTION_H
