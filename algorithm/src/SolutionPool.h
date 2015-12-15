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
	bool IsEqual(GQAP_Solution sol1, GQAP_Solution sol2);
	bool HasBetterFitness(GQAP_Solution sol, GQAP_Solution sol_ref);
	
	int CalculateHammingDistance(GQAP_Solution sol1, GQAP_Solution sol2);
	
	void OrderPool();
	
	void Replace(GQAP_Solution sol, int ReplaceIdx);
	void Insert(GQAP_Solution sol);
	
	int ReturnRandomIdx();
	int ReturnRandomIdx(std::vector<GQAP_Solution> SubPool);
	int ReturnLeastDiverseIdx(GQAP_Solution sol, std::vector<GQAP_Solution> SubPool);
	int ReturnLeastDiverseIdx(GQAP_Solution sol);
	int ReturnMostDiverseIdx(GQAP_Solution sol);
	
	
	
public:
	SolutionPool(int maxSize);
	~SolutionPool();
	
	bool Add(GQAP_Solution _sol);
	void Clear();
	
	bool IsFull();
	bool IsEmpty();
	int GetSize();
	
	GQAP_Solution GetBestSolution();
	GQAP_Solution GetMostDiverseSolution(GQAP_Solution sol);
	GQAP_Solution GetRandomSolution();
	GQAP_Solution GetSolution();
	GQAP_Solution GetSolution(int i);
	
	void PrintPool();
};

#endif // SOLUTION_POOL_H
