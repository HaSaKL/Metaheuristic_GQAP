#include "PathRelinking.h"

// C O N S T R U C T O R S

PathRelinking::PathRelinking(std::string _direction, std::string _selectMethod) {
	// Initialize Path Relinking Opbject by setting the pointer to desired direction and move selector - function
	
	SetDirection(_direction);
	SetSelectMethod(_selectMethod);
}

PathRelinking::~PathRelinking() {
}


bool PathRelinking::CheckDirection(std::string _direction) {
	// Check if the desired direction is defined
	
	if (!((_direction == "forward") || (_direction == "backward") || (_direction == "mixed"))) {
		throw std::runtime_error("Error Initializing Path-Relinking: Unknown Path-Relinking direction");
	}
}


bool PathRelinking::CheckSelectMethod(std::string _selectMethode) {
	// Check if the desird move selector is defind
	
	if (!((_selectMethode == "random") || (_selectMethode == "GRASP") || (_selectMethode == "greedy"))) {
		throw std::runtime_error("Error Initializing Path-Relinking: Unknown Move Selector direction");
	}
}


GQAP_Solution PathRelinking::step(GQAP_Solution sol_target, GQAP_Solution sol_start) {
}


GQAP_Solution PathRelinking::selectMove(std::vector<GQAP_Solution> Moves) {
}


std::vector<GQAP_Solution> PathRelinking::ConstructMoves(GQAP_Solution sol_target, GQAP_Solution sol_start) {
}


GQAP_Solution PathRelinking::operator ()(GQAP_Solution sol, SolutionPool Pool) {
}


void PathRelinking::GetDirection() {
}


void PathRelinking::SetDirection(std::string _direction) {
	// set a new direction
	CheckDirection(_direction);
	direction = _direction;
}


void PathRelinking::GetSelectMethod() {
}


void PathRelinking::SetSelectMethod(std::string _selectMethode) {
}
