#include "PathRelinking.h"

// C O N S T R U C T O R

PathRelinking::PathRelinking(int _direction = PRDirBackward, int _selectMethod = PRMethRandom) {
	// Initialize Path Relinking Object by the desired direction and move selector
	PR_Init(_direction, _selectMethod);
}


// I N I T I A L I Z E R

void PathRelinking::PR_Init(int _direction, int _selectMethod) {
	// set the Direction of Path-Relinking and Selector if it should be changed for a new PR-Run
	SetDirection(_direction);
	SetSelectMethod(_selectMethod);
}



// O P E R A T O R S
 
void PathRelinking::operator() (GQAP *_ptr_problem, GQAP_Solution _sol_target) {
	// Prepare Path-Relinking for the given starting and target solution
	// then run the path-relinking
	
	// Initialize the Toggler for mixed Path-Relinking
	mixedDirectionToggle = true;
	
	// Initialize the Incremental Evaluation for the new start
	IncrEval_Init(*_ptr_problem);
	
	// Initialize the Neighborhood for the new start and set the current solution and target solution
	_problem = _ptr_problem;
	nh.setNeighborhoodSize(_problem->GetNumEquip()),
	nh.init(*_ptr_problem, n);
	sol_target = _sol_target;
	
	// copy current solution as best solution
	sol_best = GQAP_Solution(*_problem);
	
	// execute the actual Path-Relinking
	PathRelinking::Run();
}


// S T E P    D I R E C T I O N

void PathRelinking::Run() {
	switch (PR_direction) {
		case PRDirBackward: return RunForward();
		//case PRDirForward:  return backwardStep(sol_target, sol_start);
		//case PRDirMixed:    return mixedStep(sol_target, sol_start);
		default: return RunForward();
	}
}


void PathRelinking::RunForward() {
	// the actual PR-Algorithm
	
	// Construct all possible moves
	std::vector<int> Moves = ConstructMoves();
	
	while (Moves.size() > 0) {
		DoMove(Moves);
		
		// if solution after move is better then current best solution
		// reset current best solution; do net check if equal or better,
		// if it is equal and some steps have been made, it has a smaller 
		// diversity to the target solution
		if(*_problem > sol_best) {
			sol_best = GQAP_Solution(*_problem);
		}
	}
	
	// set the solution after PR-Run to the best known solution
	*_problem = sol_best;
}

/*void PathRelinking::backwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	return forwardStep(sol_start, sol_target);
}


void PathRelinking::mixedStep(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	if (mixedDirectionToggle) {
		mixedDirectionToggle = false;
		return forwardStep(sol_target, sol_start);
	} else {
		mixedDirectionToggle = true;
		return backwardStep(sol_target, sol_start);
	}
}
*/

std::vector<int> PathRelinking::ConstructMoves() {
	// Constructs a Vector of possible moves towards the target solution
	// Do not evaluate the possible solutions, since for random selection,
	// this would be way to much effort, since only one solution is choosen 
	// reagrdless of its quality, it can be evaluated after its selections
	
	std::vector<int> Moves;
	
	for (int i = 0; i <= sol_target.solution.size(); i++) {
		if (sol_target.solution[i] != _problem->solution[i]) {
			Moves.push_back(i);
		}
	}
	
	return Moves;
}



// G E T T E R S   A N D   S E T T E R S   A N D    C H E C K E R

bool PathRelinking::CheckDirection(const int _direction) {
	// Check if the desired direction is defined
	
	if (!((_direction == PRDirForward) || (_direction == PRDirBackward) || (_direction == PRDirMixed))) {
		throw std::runtime_error("Error Initializing Path-Relinking: Unknown Path-Relinking direction");
	}
}

int PathRelinking::GetDirection() {
	return PR_direction;
}

void PathRelinking::SetDirection(const int _direction) {
	// set a new direction
	CheckDirection(_direction);
	PR_direction = _direction;
}

bool PathRelinking::CheckSelectMethod(const int _selectMethode) {
	// Check if the desird move selector is defind
	
	if (!((_selectMethode == PRMethGRASP) || (_selectMethode == PRMethGreedy) || (_selectMethode == PRMethRandom))) {
		throw std::runtime_error("Error Initializing Path-Relinking: Unknown Move Selector direction");
	}
}

int PathRelinking::GetSelectMethod() {
	return PR_selectMethod;
}

void PathRelinking::SetSelectMethod(const int _selectMethode) {
	CheckSelectMethod(_selectMethode);
	PR_selectMethod = _selectMethode;
}





// M O V E   S E L E C T O R S

void PathRelinking::DoMove(std::vector<int> Moves) {
	switch (PR_selectMethod) {
		case PRMethRandom: return DoRandomMove(Moves);
		//case PRMethGreedy: return selectGreedyMove(Moves, sol_target, sol_start);
		//case PRMethGRASP : return selectGRASPMove(Moves, sol_target, sol_start);
		default: return DoRandomMove(Moves);
	}
}


void PathRelinking::DoRandomMove(std::vector<int> Moves) {
	// Randomly Selects a Random Move and Evaluates it before return
	
	// select a random solution and remove it from the Moves-list
	int idx_move = rng.random(Moves.size());
	int idx_equip = Moves[idx_move];
	Moves.erase(Moves.begin() + idx_move);
	
	// Evaluate Move
	nh.setPosition(idx_equip);
	DoIncrEval(*_problem, n, sol_target);
	
	// Make move
	n.move(*_problem);
}

/*
GQAP_Solution PathRelinking::selectGreedyMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start) {
}

GQAP_Solution PathRelinking::selectGRASPMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start) {
}
*/
