#ifndef PATHRELINKING_H
#define PATHRELINKING_H

#include <string>
#include <vector>

#include "SolutionPool.h"
#include "GQAP_Solution.h"
#include "GQAP.h"
#include "PR_IncrEval.h"
#include "PR_Neighbor.h"

#include <neighborhood/moOrderNeighborhood.h>

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
	
	bool mixedDirectionToggle;
	
	moOrderNeighborhood<PR_Neighbor> nh;
	PR_Neighbor n;
	
	GQAP_Solution sol_target;
	GQAP_Solution sol_best;
	
	std::vector<int> ConstructMoves();
	
	bool CheckDirection(const int _direction);
	bool CheckSelectMethod(const int _selectMethod);
	
	// FIXME Function Signature
	void Run();
	void RunForward();
	//void backwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	//void mixedStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	
	void DoMove(std::vector<int> & Moves);
	void DoRandomMove(std::vector<int> & Moves);
	//void DoGreedyMove(std::vector<int> & Moves);
	//void DoGRASPMove(std::vector<int> & Moves);
	
	
public:
	PathRelinking(int _direction, int _selectMethod);
	PathRelinking();
	void PR_Init(int _direction, int _selectMethod);
	void operator() (GQAP *_ptr_problem, GQAP_Solution _sol_target);
	
	int GetDirection();
	void SetDirection(const int _direction);
	
	int GetSelectMethod();
	void SetSelectMethod(const int _selectMethode);
};

#endif // PATHRELINKING_H
