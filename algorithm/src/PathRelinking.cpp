#include "PathRelinking.h"

// C O N S T R U C T O R S

PathRelinking::PathRelinking(GQAP ptr_problem, const int _direction = PRDirBackward, const int _selectMethod = PRMethRandom) {
	// Initialize Path Relinking Object by setting the pointer to desired direction and move selector - function
	
	SetDirection(_direction);
	SetSelectMethod(_selectMethod);
	
	mixedDirectionForward = true;
	
	IncrEval_Init(* _problem);
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


std::vector<int> PathRelinking::ConstructMoves(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	// Constructs a Vector of possible moves towards the target solution
	// Do not evaluate the possible solutions, since for random selection,
	// this would be way to much effort, since only one solution is choosen 
	// reagrdless of its quality, it can be evaluated after its selections
	
	std::vector<int> Moves;
	
	for (int i = 0; i <= sol_target.solution.size(); i++) {
		if (sol_target.solution[i] != sol_start.solution[i]) {
			Moves.push_back(i);
		}
	}
	
	return Moves;
}


GQAP_Solution PathRelinking::operator ()(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	// Do the actual Path-Relinking
	
	//return sol;
}


// S T E P    D I R E C T I O N

GQAP_Solution PathRelinking::step(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	switch (PR_direction) {
		case PRDirBackward: return forwardStep(sol_target, sol_start);
		case PRDirForward:  return backwardStep(sol_target, sol_start);
		case PRDirMixed:    return mixedStep(sol_target, sol_start);
		default: return forwardStep(sol_target, sol_start);
	}
}


GQAP_Solution PathRelinking::forwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start) {
}


GQAP_Solution PathRelinking::backwardStep(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	return forwardStep(sol_start, sol_target);
}


GQAP_Solution PathRelinking::mixedStep(GQAP_Solution sol_target, GQAP_Solution sol_start) {
	if (mixedDirectionForward) {
		mixedDirectionForward = false;
		return forwardStep(sol_target, sol_start);
	} else {
		mixedDirectionForward = true;
		return backwardStep(sol_target, sol_start);
	}
}


// M O V E   S E L E C T O R S

GQAP_Solution PathRelinking::selectMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start) {
	switch (PR_selectMethod) {
		case PRMethRandom: return selectRandomMove(Moves, sol_target, sol_start);
		case PRMethGreedy: return selectGreedyMove(Moves, sol_target, sol_start);
		case PRMethGRASP : return selectGRASPMove(Moves, sol_target, sol_start);
		default: return selectRandomMove(Moves, sol_target, sol_start);
	}
}


GQAP_Solution PathRelinking::selectRandomMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start) {
	// Randomly Selects a Random Move and Evaluates it befor return
	
	int idx = Moves[rng.random(Moves.size())];
	
	GQAP_Solution tmp = sol_start;
	tmp[idx] = sol_target[idx];
	
	//IncrEval(sol_start, sol_target, idx);
	
	return sol_start;
	
}

GQAP_Solution PathRelinking::selectGreedyMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start) {
}

GQAP_Solution PathRelinking::selectGRASPMove(std::vector<int> Moves, GQAP_Solution sol_target, GQAP_Solution sol_start) {
}

