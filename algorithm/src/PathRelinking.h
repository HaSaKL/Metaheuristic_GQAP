#ifndef PATHRELINKING_H
#define PATHRELINKING_H

#include <string>
#include <vector>

#include "SolutionPool.h"
#include "GQAP_Solution.h"
#include "PR_MoveSelector.h"
#include "PR_Step.h"

class PathRelinking
{
private:
	
	std::string direction;
	std::string selectMethod;
	
	bool CheckDirection(std::string _direction);
	bool CheckSelectMethod(std::string _selectMethod);
	
	PR_Step *stepFunction;
	PR_MoveSelector *selectMoveFunction;
	
	GQAP_Solution step(GQAP_Solution sol_target, GQAP_Solution sol_start);
	GQAP_Solution selectMove(std::vector<GQAP_Solution> Moves);
	
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
