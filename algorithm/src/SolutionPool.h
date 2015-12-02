#ifndef SOLUTION_POOL_H
#define SOLUTION_POOL_H

#include "GQAP_Solution.h"
#include <vector>
#include <algorithm>

class SolutionPool {
	
private:
	std::vector<GQAP_Solution> Pool;
	int maxPoolSize;
	
	bool IsInPool(const GQAP_Solution sol);
	bool IsEqual(const GQAP_Solution sol1, const GQAP_Solution sol2);
	bool HasBetterFitness(const GQAP_Solution sol, const GQAP_Solution sol_ref);
	
	int CalculateHammingDistance(GQAP_Solution sol1, GQAP_Solution sol2);
	
	void OrderPool();
	
	void Replace(GQAP_Solution sol, int ReplaceIdx);
	void Insert(GQAP_Solution sol);
	
	int ReturnRandomIdx();
	int ReturnRandomIdx(std::vector<GQAP_Solution> SubPool);
	int ReturnDiverseIdx(GQAP_Solution sol, std::vector<GQAP_Solution> SubPool);
	int ReturnDiverseIdx(GQAP_Solution sol);
	
	
	
public:
	SolutionPool(int maxSize);
	~SolutionPool();
	
	bool Add(GQAP_Solution _sol);
	GQAP_Solution Clear();
	
	void PrintPool();
};

#endif // SOLUTION_POOL_H
