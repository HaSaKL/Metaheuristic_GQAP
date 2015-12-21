#ifndef PATHRELINKING_H
#define PATHRELINKING_H

#include <string>
#include <vector>

#include "GQAP_CLI.h"

#include "SolutionPool.h"
#include "GQAP_Solution.h"
#include "GQAP.h"
#include "PR_IncrEval.h"
#include "PR_Neighbor.h"

#include "GRASP_Alpha.h"
#include "GRASP_FixedAlpha.h"
#include "GRASP_ReactiveAlpha.h"
#include "GRASP_UniformRandomAlpha.h"

#include <neighborhood/moOrderNeighborhood.h>

class PathRelinking: public PR_IncrEval
{
private:
	int PR_direction;
	int PR_selectMethod;
	
	moOrderNeighborhood<PR_Neighbor> nh;
	PR_Neighbor n;
	
	GQAP_Solution sol_target;
	GQAP_Solution sol_best;
	
	GRASP_Alpha * alpha_gen;
	
	std::vector<int> ConstructMoves();
	
	bool CheckDirection(const int _direction);
	bool CheckSelectMethod(const int _selectMethod);
	
	// FIXME Function Signature
	void Run();
	void RunForward();
	void RunBackward();
	void RunMixed();
	
	void DoMove(std::vector<int> & Moves);
	void DoRandomMove(std::vector<int> & Moves);
	void DoGreedyMove(std::vector<int> & Moves);
	void DoGRASPMove(std::vector<int> & Moves);
	
	typedef std::pair<double, int> MovePairType;
	
public:
	PathRelinking(int _direction, int _selectMethod);
	PathRelinking();
	~PathRelinking();
	
	void PR_Init(int _direction, int _selectMethod);
	void operator() (GQAP *_ptr_problem, GQAP_Solution _sol_target);
	
	int GetDirection();
	void SetDirection(const int _direction);
	
	int GetSelectMethod();
	void SetSelectMethod(const int _selectMethode);
};

#endif // PATHRELINKING_H
