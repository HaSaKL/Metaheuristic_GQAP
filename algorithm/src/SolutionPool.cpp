#include "SolutionPool.h"

SolutionPool::SolutionPool(int maxSize) {
	maxPoolSize = maxSize;
	
	Pool = std::vector<GQAP_Solution>();
}

SolutionPool::~SolutionPool() {
}

int SolutionPool::CalculateHammingDistance(GQAP_Solution sol1, GQAP_Solution sol2) {
	// Calculates the Hamming Distance between two solution
	int distance = 0;
	
	for (int i = 0; i <= sol1.solution.size(); i++) {
		if (sol1.solution[i] != sol2.solution[i]) {
			distance++;
		}
	}
	
	//DEBUG
	std::cout << "Diversity of " << std::endl;
	sol1.printSolution();
	sol2.printSolution();
	std::cout << "--> " << distance << std::endl << std::endl;
	// */ 
	
	return distance;
}


bool SolutionPool::Add(GQAP_Solution sol) {
	// Will check if a Solution can be added (return true, false if not) and
	// will add it if possible.
	// Solutions will always be added if the maximum pool size has
	// not been reached. once the Pool is full, a solution is always added
	// if it has the a better fitness value then the best known value, if it 
	// is at least better then the worse value in the pool it will replace an
	// element which has no higher firness value and is most similar to the entering
	// solution, if there is any. Otherwise it will not enter the pool
	
	// If Pool is not full, solutions will always be added
	if ( (Pool.size() < maxPoolSize) && (!IsInPool(sol)) ) {
			Insert(sol);
			return true;
	}
	
	// If Pool is full, solution will only be added if it is at least better than the worst solution
	if (sol < Pool.front() ) {
		
		// DEBUG
		//std::cout << "Solution not good enogh" << std::endl;
		
		return false;
	}
	
	// get set of worse solutions
	int idx = 0;
	while (HasBetterFitness(Pool[idx], sol)) {
		idx++;
	}
	
	// get index of most diverse solution within this pool
	std::vector<GQAP_Solution> WorseSolutions(Pool.begin() , Pool.begin() + idx);
	int SwapIdx = ReturnDiverseIdx(sol, WorseSolutions);
	
	// replace element
	Replace(sol, SwapIdx);
	
	
	return true;
	
}


void SolutionPool::Insert(GQAP_Solution sol) {
	// Adds a Solution to the end of the solution pool
	// and sorts the pool afterwards
	
	Pool.push_back(sol);
	
	OrderPool();
}


void SolutionPool::Replace(GQAP_Solution sol, int ReplaceIdx) {
	// Replaces the current solution with index ReplaceIdx with sol
	// and sorts the pool according to Fitness
	
	Pool[ReplaceIdx] = sol;
	
	OrderPool();
}


void SolutionPool::OrderPool() {
	// Orders the Pool according to the solutions' Fitness
	
	std::sort(Pool.begin(), Pool.end());
}


bool SolutionPool::IsInPool(const GQAP_Solution sol) {
	// checks if sol is already in the pool
	for (int i = 0; i < Pool.size(); i++) {
		if (IsEqual(sol, Pool[i])) {
			return true;
		}
	}
	
	return false;
}


bool SolutionPool::IsEqual(const GQAP_Solution sol1, const GQAP_Solution sol2) {
	// return true if sol1 and sol2 are equal
	
	// this function cannot use std::equal because of the eoVector-Data type
	for (int i=0; i < sol1.solution.size(); i++) {
		if (sol1.solution[i] != sol2.solution[i]) {
			return false;
		}
	}
	
	return true;
}


bool SolutionPool::HasBetterFitness(const GQAP_Solution sol, const GQAP_Solution sol_ref) {
	// returns true if the fitness of sol is better then sol_ref
	
	return sol.fitness() < sol_ref.fitness();
}


int SolutionPool::ReturnRandomIdx() {
	// Returns a Random Solution from the Solution Pool
	
	return rng.random(Pool.size());
}


int SolutionPool::ReturnRandomIdx(std::vector<GQAP_Solution> SubPool) {
	// Return a Random Solution from a given Pool of possible solutions
	
	return rng.random(SubPool.size());
}


int SolutionPool::ReturnDiverseIdx(GQAP_Solution sol, std::vector<GQAP_Solution> SubPool) {
	// Returns the Solution from a Pool which is least diverse from sol,
	// If more then one solution has the same Diversity, one of those
	// is choosen randomly
	
	std::vector<int> diversity(SubPool.size());
	
	// DBEUG
	//std::cout << "Subpool made with size " << SubPool.size() << std::endl;
	
	// calculate the diverisy of each solution in the pool based on input solution
	for (int i = 0; i < SubPool.size(); i++) {
		diversity[i] = CalculateHammingDistance(sol, SubPool[i]);
	}
	
	// get the maximum diversity
	int minDiversity = *std::min_element(diversity.begin(), diversity.end());
	
	// collect indices of all solutions in the pool with the maximum diversiry
	std::vector<int> minIndex(0);
	for (int i = 0; i <= SubPool.size(); i++) {
		if (diversity[i] == minDiversity) {
			minIndex.push_back(i);
		}
	}
	
	// return a random solution from the set of solutions with the highest diversity
	return minIndex[ rng.random( minIndex.size() ) ];
}


int SolutionPool::ReturnDiverseIdx(GQAP_Solution sol) {
	// Returns the Solution from the Solution Pool which is least diverse from sol
	
	return ReturnDiverseIdx(sol, Pool);
}


GQAP_Solution SolutionPool::Clear(){
	
	// empties the Solution Pool
	
	Pool.clear();
}

void SolutionPool::PrintPool() {
	// for Debug-purposes
	// prints the entire pool
	
	std::cout << "Pool contains " << Pool.size() << " of maximum " << maxPoolSize << " Solutions " << std::endl;
	for (int i = 0; i < Pool.size(); i++) {
		std::cout << i << ": " << Pool[i].fitness() << " ";
		Pool[i].printSolution();
	}
}
