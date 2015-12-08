#ifndef PATHRELINKING_H
#define PATHRELINKING_H

#include <string>
#include <vector>

#include "SolutionPool.h"
#include "GQAP_Solution.h"
#include "GQAP.h"
#include "PR_IncrEval.h"
#include "PR_Neighbor.h"

class PathRelinking: public PR_IncrEval
{
private:
	// FIXME: Move constants to somewhere else? e.g. in the CLI.h?
	// this could also save the CheckDirection and CheckSelectMethod functions
	static const int PRDirForward 	= 0;
	static const int PRDirBackward 	= 1;
	static const int PRDirMixed 	= 2;
	
	static const int PRMethRandom = 0;
	static const int PRMethGreedy = 1;
	static const int PRMethGRASP  = 2;
	  
	int PR_direction;
	int PR_selectMethod;
	
	bool mixedDirectionForward;
	
	bool CheckDirection(const int _direction);
	bool CheckSelectMethod(const int _selectMethod);
	
	GQAP_Solution step(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution forwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution backwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution mixedStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	
	GQAP_Solution selectMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution selectRandomMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution selectGreedyMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution selectGRASPMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start);
	
	std::vector<int> ConstructMoves(GQAP_Solution sol_target, GQAP_Solution sol_start);
	
public:
	PathRelinking(GQAP ptr_problem, const int _direction, const int _selectMethod);
	~PathRelinking();
	
	GQAP_Solution operator() (GQAP_Solution sol_target, GQAP_Solution sol_start);
	
	int GetDirection();
	void SetDirection(const int _direction);
	
	int GetSelectMethod();
	void SetSelectMethod(const int _selectMethode);
};

#endif // PATHRELINKING_H
