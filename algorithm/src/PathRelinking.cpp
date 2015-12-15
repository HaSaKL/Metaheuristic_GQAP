#include "PathRelinking.h"

// C O N S T R U C T O R

PathRelinking::PathRelinking(int _direction = PRDirBackward, int _selectMethod = PRMethRandom) {
	// Initialize Path Relinking Object by the desired direction and move selector
	alpha_gen = NULL;
	PR_Init(_direction, _selectMethod);
}

PathRelinking::PathRelinking() {
	alpha_gen = NULL;
	PR_Init(PRDirBackward, PRMethRandom);
}

PathRelinking::~PathRelinking() {
	// also detroy the alpha-generator
	delete alpha_gen;
}

// I N I T I A L I Z E R

void PathRelinking::PR_Init(int _direction, int _selectMethod) {
	// set the Direction of Path-Relinking and Selector if it should be changed for a new PR-Run
	SetDirection(_direction);
	SetSelectMethod(_selectMethod);
	
	// If Selector works with Alpha-Value: Initialize Alpha-Generator
	if (PR_selectMethod == PRMethGRASP) {
		// CHECKME: For more advanced implementation another alpha-generator (e.g. teh default for the algorithm?)
		// could also be initialized and used; make sure to initialize it!!!
		alpha_gen = new GRASP_FixedAlpha(0.2);
	}
	
}



// O P E R A T O R S
 
void PathRelinking::operator () (GQAP *_ptr_problem, GQAP_Solution _sol_target) {
	// Prepare Path-Relinking for the given starting and target solution
	// then run the path-relinking
	
	// DEBUG
	//std::cout << "Initializing Path-Relinking for new run ..." << std::endl;
	
	// Initialize the Incremental Evaluation for the new start
	IncrEval_Init(*_ptr_problem);
	
	// Initialize the Neighborhood for the new start and set the current solution and target solution
	_problem = _ptr_problem;
	nh.setNeighborhoodSize(_problem->GetNumEquip()),
	nh.init(*_ptr_problem, n);
	
	sol_target = _sol_target;
	
	if (sol_target > *_problem) {
		sol_best = _sol_target;
	} else {
		sol_best = *_problem;
	}
	
	/*// DEBUG
	std::cout << "Sol Target Fitness: " << sol_target.fitness() << std::endl;
	std::cout << "Sol Current Fitness: " << _problem->fitness() << std::endl;
	std::cout << "Sol Best Fitness: " << sol_best.fitness() << std::endl;
	// */
	
	// execute the actual Path-Relinking
	PathRelinking::Run();
}


// S T E P    D I R E C T I O N

void PathRelinking::Run() {
	switch (PR_direction) {
		case PRDirForward: 	RunForward();  break;
		case PRDirBackward: RunBackward(); break;
		case PRDirMixed: 	RunMixed();    break;
	}
}


void PathRelinking::RunForward() {
	// the actual PR-Algorithm
	
	// Construct all possible moves
	std::vector<int> Moves = ConstructMoves();
	
	while (Moves.size() > 0) {
		
		/* //DEBUG
		std::cout << std::endl << std::endl;;
		std::cout << "Possible Moves: " << Moves.size() << std::endl;  
		// */
		
		DoMove(Moves);
		
		// if solution after move is better then current best solution
		// reset current best solution; do net check if equal or better,
		// if it is equal and some steps have been made, it has a smaller 
		// diversity to the target solution
		
		//if(_problem->fitness() > sol_best.fitness()) {
		if(*_problem > sol_best) {	
			
			sol_best = GQAP_Solution(*_problem);
			
			/*// DEBUG
			std::cout << "Better Solution found!: ";
			sol_best.printSolution();
			std::cout << sol_best.fitness() << std::endl;
			
		} else {
			std::cout << "Not Better Soluion found!" << std::endl;
			sol_best.printSolution();
			std::cout << sol_best.fitness() << std::endl;
		//*/	
		}
	}
	
	// set the solution after PR-Run to the best known solution
	*_problem = sol_best;
}

void PathRelinking::RunBackward() {
	// Just like run forward but in different direction.
	// this means run forward can be called but the starting and 
	// target solutions need to be changed
	
	GQAP_Solution tmp;
	tmp = sol_target;
	sol_target = GQAP_Solution(*_problem);
	*_problem = tmp;
	
	RunForward();
}

void PathRelinking::RunMixed() {
	// Alternate the direction of the path relinking
	// do this by slightliy modifiying the forward path-relinking
	// by toggeling the problem and target solution
	// this makes it computational more expensive
	// possible alternative would be a differend method-definition
	// but NOT using neighborhoods
	
	GQAP p1 = *_problem;
	GQAP p2 = *_problem;
	p2 = sol_target;
	
	bool toggleDir = true;
	
	GQAP* problem_ptr = _problem;
	
	//GQAP_Solution t1 = sol_target;
	//GQAP_Solution t2 = GQAP_Solution(p1);
	
	
	// Moves are independent of PR-Direction
	std::vector<int> Moves = ConstructMoves();
	
	while(Moves.size() > 0) {
		if (toggleDir) {
			_problem = & p1;
			sol_target = GQAP_Solution(p2);
			
			/*// DEBUG
			std::cout << "--------Before Move:---------" << std::endl;
			std::cout << "Starting Sol: " << _problem->fitness() << " ";
			_problem->printSolution();
			std::cout << "Target Sol:   " << sol_target.fitness() << " ";
			sol_target.printSolution();
			std::cout << "-----------------------------" << std::endl << std::endl;
			//*/
			
			DoMove(Moves);
			toggleDir = false;
			
			/*// DEBUG
			std::cout << "--------After Move:---------" << std::endl;
			std::cout << "Starting Sol: " << _problem->fitness() << " ";
			_problem->printSolution();
			std::cout << "Target Sol:   " << sol_target.fitness() << " ";
			sol_target.printSolution();
			std::cout << "-----------------------------" << std::endl << std::endl;
			//*/
			
		} else {
			_problem = & p2;
			sol_target = GQAP_Solution(p1);
			
			/*// DEBUG
			std::cout << "--------Before Move:---------" << std::endl;
			std::cout << "Starting Sol: " << _problem->fitness() << " ";
			_problem->printSolution();
			std::cout << "Target Sol:   " << sol_target.fitness() << " ";
			sol_target.printSolution();
			std::cout << "-----------------------------" << std::endl << std::endl;
			//*/
			
			DoMove(Moves);
			toggleDir = true;
			
			/*// DEBUG
			std::cout << "--------After Move:---------" << std::endl;
			std::cout << "Starting Sol: " << _problem->fitness() << " ";
			_problem->printSolution();
			std::cout << "Target Sol:   " << sol_target.fitness() << " ";
			sol_target.printSolution();
			std::cout << "-----------------------------" << std::endl << std::endl;
			//*/
		}
		if(*_problem > sol_best) {	
			sol_best = GQAP_Solution(*_problem);
		}
	}
	
	// set the solution after PR-Run to the best known solution
	_problem = problem_ptr;
	*_problem = sol_best;
}


std::vector<int> PathRelinking::ConstructMoves() {
	// Constructs a Vector of possible moves towards the target solution
	// Do not evaluate the possible solutions, since for random selection,
	// this would be way to much effort, since only one solution is choosen 
	// reagrdless of its quality, it can be evaluated after its selections
	
	std::vector<int> Moves;
	
	for (int i = 0; i < sol_target.solution.size(); i++) {
		if (sol_target.solution[i] != _problem->solution[i]) {
			Moves.push_back(i);
		}
	}
	
	 /*//DEBUG - List Moves
	std::cout << std::endl;
	std::cout << "----------------- Constructing Moves -----------" << std::endl; 
	std::cout << "Target Solution: "; sol_target.printSolution();
	std::cout << "Start Solution:  "; _problem->printSolution();
	std::cout << "Possible Flip Position:" << std::endl;
	for (int i = 0; i < Moves.size(); i++) {
		std::cout << "Move Index " << i << " Flip Equipment " << Moves[i] << std::endl; 
	}
	std::cout << "------------------------------------------------" << std::endl; 
	//*/
	
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

void PathRelinking::DoMove(std::vector<int> & Moves) {
	switch (PR_selectMethod) {
		case PRMethRandom: DoRandomMove(Moves); break;
		case PRMethGreedy: DoGreedyMove(Moves); break;
		case PRMethGRASP : DoGRASPMove(Moves); break;
	}
}


void PathRelinking::DoRandomMove(std::vector<int> & Moves) {
	// Randomly Selects a Random Move and Evaluates it before return
	
	// select a random solution and remove it from the Moves-list
	int idx_move = rng.random(Moves.size());
	int idx_equip = Moves[idx_move];
	Moves.erase(Moves.begin() + idx_move);
	
	//std::cout << "DEBUG Chosen Index Move: " << idx_move << " --> Equip " << idx_equip << std::endl;
	
	//set neighbor to choosen move, default after initialization is to move equipment 0
	nh.init(*_problem, n);
	if (idx_equip > 0) {
		nh.setPosition(idx_equip-1);
		nh.next(*_problem, n);
	}
	
	/*// DEBUG
	std::cout << "DEBUG: DoIncrEval..." << std::endl;
	std::cout << "Position in NH: " << nh.position() << std::endl;
	std::cout << "Current Fitness: " << _problem->fitness() << std::endl << std::endl;
	//*/
	
	// Evaluate Move
	DoIncrEval(*_problem, n, sol_target);
	
	/*//DEBUG
	std::cout << "Key in neighbor: " << n.getKey() << std::endl;
	std::cout << "New Fitness:     " << n.fitness() << std::endl;
	std::cout << "Doing " << idx_move << " (equipment " << idx_equip << ") NOW" << std::endl;
	//*/
	
	// Make move
	n.move(*_problem,sol_target);
}


void PathRelinking::DoGreedyMove(std::vector<int> & Moves) {
	// Evaluate all possible moves and do the best move
	
	int idx_pos;	// Holding Position of best Move
	int idx_move;	// Holding Index of best Move in Move-Vector
	
	// Holds the best Improvement
	double bestVal = std::numeric_limits<double>::max() - 1;
	
	// initialize the neighbor hood for the current solution
	nh.init(*_problem, n);
	
	for (int i = 0; i < Moves.size(); i++) {
		
		// set position of current move. Must not be realized for move zero, 
		// which is supposed to be the first if it is valid at all! 
		// This is ensured by ConstructMoves
		
		if (Moves[i] > 0) {
			nh.setPosition(Moves[i]-1); // set to -1 so next can jump to correct solution
			nh.next(*_problem, n);
		}
		
		/*// DEBUG
		std::cout << "DEBUG: DoIncrEval..." << std::endl;
		std::cout << "Position in NH: " << nh.position() << std::endl;
		std::cout << "Current Fitness: " << _problem->fitness() << std::endl << std::endl;
		//*/
		
		// Evaluate move
		DoIncrEval(*_problem, n, sol_target);
		
		//std::cout << "DEBUG: Testing for and setting best move against neighbor fitness: " << bestVal << " (Position " <<  idx_move << ") > " << n.fitness() << std::endl;
		
		// set the best move
		if (bestVal > n.fitness()) {
			
			//std::cout << "DEBUG:: Setting best val " << std::endl;
			
			bestVal = n.fitness();
			
			//std::cout << "DEBUG: Accessing Moves[" << i << "]" << std::endl << std::endl;
			
			idx_pos = Moves[i];
			idx_move = i;
		}
	}
		
	//std::cout << "DEBUG: Erasing Move with idx " << idx_move << " (Position " << Moves[idx_move] << ")" << std::endl;	
		
	// erase the best move from the move list
	Moves.erase(Moves.begin() + idx_move);
	
	//std::cout << "DEBUG: Setting Neighbor to Position " << idx_pos << std::endl;
	
	// set neighbot to best known move
	if (idx_pos > 0) {
		nh.setPosition(idx_pos-1);
		nh.next(*_problem, n);
	} else { // if position zero had the best improvement
		nh.init(*_problem, n);
	}
	
	//std::cout << "Executing Move ..." << std::endl;
	
	// evaluate and execute this move
	// re evaluation is needed b/c neighborhood was moved around and Fitness needs to be set
	DoIncrEval(*_problem, n, sol_target);
	n.move(*_problem, sol_target);
}


void PathRelinking::DoGRASPMove(std::vector<int> & Moves) {
	// Evaluate all possible moves and choose a suitable move from the list according to a GRASP scheme
	
	
	// Vector holding the fitness value of each possible move
	std::vector<MovePairType> MovePair;
	MovePair.resize(Moves.size());
	
	// initialize the neighbor hood for the current solution
	nh.init(*_problem, n);
	
	
	// Evaluate all moves and store fitness values in MoveFitness
	for (int i = 0; i < Moves.size(); i++) {
		
		// set position of current move. Must not be realized for move zero, 
		// which is supposed to be the first if it is valid at all! 
		// This is ensured by ConstructMoves
		if (Moves[i] > 0) {
			nh.setPosition(Moves[i]-1); // set to -1 so next can jump to correct solution
			nh.next(*_problem, n);
		}
		
		// Evaluate move
		DoIncrEval(*_problem, n, sol_target);
		
		// store result in vector
		MovePair[i].first = n.fitness();
		MovePair[i].second = i;
	}
	
	
	/*//DEBUG
	std::cout << "RCL - Contents: " << std::endl;
	std::cout << "idx  Fitness" << std::endl;
	for (int i = 0; i < MovePair.size(); i++) {
		std::cout << MovePair[i].second << "    " << MovePair[i].first << std::endl;
	}
	std::cout << std::endl;
	// */
	
	
	
	// choose index using GRASP-Procedure
	
	// sort the moves and choose from an RCL based on the sorted moves
	std::sort(MovePair.begin(), MovePair.end());
	
	/*//DEBUG
	std::cout << "RCL - Contents after sort: " << std::endl;
	std::cout << "idx  Fitness" << std::endl;
	for (int i = 0; i < MovePair.size(); i++) {
		std::cout << MovePair[i].second << "    " << MovePair[i].first << std::endl;
	}
	std::cout << std::endl;
	// */
	
	
	double alpha = alpha_gen->operator ()(*_problem);
	
	double minFitness = MovePair.front().first;
	double maxFitness = MovePair.back().first;
	double maxRCLFit  = minFitness + alpha * (maxFitness - minFitness);
	
	// find first index of sorted RCL list element with higher then cut-off costs
	// implementaion using std::upper_bound does not work b/c of type is pair
	int cutOff_idx = 0;
	while (cutOff_idx < MovePair.size()) {
		if(MovePair[cutOff_idx].first >= maxRCLFit) {
			break;
		} else {
			cutOff_idx++;
		}
	}
	
	// choose an pair from the RCL randomly
	int idx_GRASP = rng.random(cutOff_idx + 1);
	
	// set idx_pos and idx_move to values from the choosen RCL Element
	int idx_move = MovePair[idx_GRASP].second;
	int idx_pos  = Moves[idx_move];
		
	/*// DEBUG	
	std::cout << "idx_move    : " << idx_move << std::endl;
	std::cout << "CutOff Index: " << cutOff_idx << std::endl;
	std::cout << "idx_GRASP   : " << idx_GRASP << "--> Fitness: " << MovePair[idx_GRASP].first << " Pos: " << MovePair[idx_GRASP].second << std::endl;
	std::cout << "idx_pos     : " << idx_pos << "--> Moves[idx-move] = " << Moves[idx_move] << std::endl;
	std::cout << "DEBUG: Erasing Move with idx " << idx_move << " (Position " << idx_pos << ") @ Moves.size = " << Moves.size() << std::endl;	
	// */
		
	// erase the best move from the move list
	Moves.erase(Moves.begin() + idx_move);
	
	//std::cout << "DEBUG: Setting Neighbor to Position " << idx_pos << std::endl;
	
	// set neighbot to selected move
	if (idx_pos > 0) {
		nh.setPosition(idx_pos-1);
		nh.next(*_problem, n);
	} else { // if position zero had the best improvement
		nh.init(*_problem, n);
	}
	
	//std::cout << "DEBUG: Executing Move ..." << std::endl;
	
	// evaluate and execute this move
	// re evaluation is needed b/c neighborhood was moved around and Fitness needs to be set
	DoIncrEval(*_problem, n, sol_target);
	n.move(*_problem, sol_target);
}

