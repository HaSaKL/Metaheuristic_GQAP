#ifndef PATHRELINKING_H
#define PATHRELINKING_H

#include <string>
#include <vector>

#include "SolutionPool.h"
#include "GQAP_Solution.h"

class PathRelinking
{
private:
	// FIXME: Move this to somewhere else?
	const int PRDirForward =  0;
	const int PRDirBackward = 1;
	const int PRDirMixed = 2;
	
	const int PRMethRandom = 0;
	const int PRMethGreedy = 1;
	const int PRMethGRASP  = 2;
	
	std::string direction;
	std::string selectMethod;
	
	bool CheckDirection(std::string _direction);
	bool CheckSelectMethod(std::string _selectMethod);
	
	GQAP_Solution step(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution forwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution backwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution mixedStep(GQAP_Solution sol_target, GQAP_Solution sol_start);
	
	GQAP_Solution selectMove(std::vector<GQAP_Solution> Moves);
	GQAP_Solution selectRandomMove(std::vector<GQAP_Solution> Moves);
	GQAP_Solution selectGreedyMove(std::vector<GQAP_Solution> Moves);
	GQAP_Solution selectGRASPMove(std::vector<GQAP_Solution> Moves);
	
	std::vector<GQAP_Solution> ConstructMoves(GQAP_Solution sol_target, GQAP_Solution sol_start);
	
public:
	PathRelinking(std::string direction, std::string _selectMethode);
	PathRelinking();
	~PathRelinking();
	
	GQAP_Solution operator() (GQAP_Solution sol, SolutionPool Pool);
	
	void GetDirection();
	void SetDirection(std::string _direction);
	
	void GetSelectMethod();
	void SetSelectMethod(std::string _selectMethode);
};

#endif // PATHRELINKING_H
