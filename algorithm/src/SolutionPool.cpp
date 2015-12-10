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
	
	/*//DEBUG
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
	//std::cout << "DEBUG: Checking to see if pool is full ... " << std::endl;
	if ( !IsFull() && !IsInPool(sol) ) {
			Insert(sol);
			return true;
	}
	
	
	// If Pool is full, solution will only be added if it is at least better than the worst solution
	
	//std::cout << "DEBUG Fitness GQAP_Sol: " << sol.fitness() << std::endl;
	//std::cout << "DEBUG Fitness Pool.front: " << Pool.front().fitness() << std::endl;
	
	//std::cout << "DEBUG: Checking to if solution is at least better than worst solution ... " << std::endl;
	if (sol < Pool.front() ) {
		
		// DEBUG
		//std::cout << "Solution not good enogh" << std::endl;
		
		return false;
	}
	
	
	// get set of worse solutions
	//std::cout << "DEBUG: Get set of worse solutions ... " << std::endl;
	//std::cout << "DEBUG: Pool.size = " << Pool.size() << std::endl;
	int idx = 0;
	while (idx < Pool.size()) {
		//std::cout << "DEBUG: Current: HasBetterFitness(sol,Pool["<<idx<<"]): " << sol.fitness() << " vs. " << Pool[idx].fitness() << ": " << (sol > Pool[idx]) << std::endl;
		if (HasBetterFitness(sol,Pool[idx])) {
			idx++;
		} else {
			break;
		}
		//std::cout << "DEBUG: NEXT: HasBetterFitness(sol,Pool["<<idx<<"]) " << std::endl;
	}
	
	// get index of most diverse solution within this pool
	//std::cout << "DEBUG: Getting Index of Worse Solutions ... " << std::endl;
	std::vector<GQAP_Solution> WorseSolutions(Pool.begin() , Pool.begin() + idx);
	int SwapIdx = ReturnLeastDiverseIdx(sol, WorseSolutions);
	
	
	// replace element
	//std::cout << "DEBUG: Calling Replace with SwapIdx " << SwapIdx << std::endl;
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
		if (Pool[i] == sol) {
			return true;
		}
	} 
	
	return false;
}


bool SolutionPool::HasBetterFitness(GQAP_Solution sol, GQAP_Solution sol_ref) {
	// returns true if the fitness of sol is better then sol_ref
	//std::cout << "DEBUG: CallindHasBetterFitness" << std::endl;
	return !(sol < sol_ref);
}


int SolutionPool::ReturnRandomIdx() {
	// Returns a Random Solution from the Solution Pool
	
	return rng.random(Pool.size());
}


int SolutionPool::ReturnRandomIdx(std::vector<GQAP_Solution> SubPool) {
	// Return a Random Solution from a given Pool of possible solutions
	
	return rng.random(SubPool.size());
}


int SolutionPool::ReturnLeastDiverseIdx(GQAP_Solution sol, std::vector<GQAP_Solution> SubPool) {
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


int SolutionPool::ReturnLeastDiverseIdx(GQAP_Solution sol) {
	// Returns the Solution from the Solution Pool which is least diverse from sol
	
	return ReturnLeastDiverseIdx(sol, Pool);
}


int SolutionPool::ReturnMostDiverseIdx(GQAP_Solution sol) {
	// Returns the Solution from a Pool which is most diverse from sol,
	// If more then one solution has the same Diversity, one of those
	// is choosen randomly
	
	std::vector<int> diversity(Pool.size());
	
	
	// calculate the diverisy of each solution in the pool based on input solution
	for (int i = 0; i < Pool.size(); i++) {
		diversity[i] = CalculateHammingDistance(sol, Pool[i]);
	}
	
	// get the maximum diversity
	int maxDiversity = *std::max_element(diversity.begin(), diversity.end());
	
	// collect indices of all solutions in the pool with the maximum diversiry
	std::vector<int> maxIndex(0);
	for (int i = 0; i <= Pool.size(); i++) {
		if (diversity[i] == maxDiversity) {
			maxIndex.push_back(i);
		}
	}
	
	// return a random solution from the set of solutions with the highest diversity
	return maxIndex[ rng.random( maxIndex.size() ) ];
}

void SolutionPool::Clear(){
	
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


bool SolutionPool::IsFull() {
	// returns true if there are maxPoolSize solutions in the pool
	
	return (Pool.size() >= maxPoolSize);
	
}


bool SolutionPool::IsEmpty() {
	// return true if the pool is empty
	
	return (Pool.size() <= 0);
}

int SolutionPool::GetSize() {
	// returns the number of elements in the solution pool
	
	return Pool.size();
}

GQAP_Solution SolutionPool::GetMostDiverseSolution(GQAP_Solution sol) {
	// returns solution most diverse from sol, if there are several with the same
	// diversity on of those is returned randomly
	
	return Pool[ReturnMostDiverseIdx(sol)];
}

GQAP_Solution SolutionPool::GetRandomSolution() {
	// randomly returns a solution from the pool
	
	return Pool[ReturnRandomIdx()];
}

GQAP_Solution SolutionPool::GetBestSolution() {
	// returns the best solution in the pool
	
	return Pool.back();
}
