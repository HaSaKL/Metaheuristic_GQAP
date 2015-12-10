#include <iostream>
#include <string>

// neede eo headers
#include <eo>
#include <neighborhood/moOrderNeighborhood.h>

// Problem Specific headers
#include "GQAP.h"
#include "GQAP_Eval.h"
#include "SolutionPool.h"
#include "PathRelinking.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "Metaheuristic for the GQAP compiled at " << __DATE__ << " " << __TIME__ << std::endl;
		std::cout << "Path-Relinking Test" << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
		
		std::cout << "Loading Problem \"";
		
		std::string fileName = "../../../test_instances/own_instances/mini_test_instances/4-2.txt";
		//std::string fileName = "../../../test_instances/from_literature/original_format/cordeau/20-15-35.txt";
		std::cout << fileName << "\"" << std::endl;
		
		// Initialize Problem
		GQAP p(fileName);
		std::cout << "... done. " << std::endl << std::endl;
		
		// Define problem functions for cleaner code
		GQAP_Eval FullEval;
		
		// Define an empty solution Pool
		int poolSize = 10;
		SolutionPool Pool(poolSize);
		
		// fill pool with random solution
		for (int i = 0; i < poolSize; i++) {
			p.GRASPInit(0.4);
			FullEval(p);
			Pool.Add(p);
		}
		Pool.PrintPool();
		
		// Intialize the Path-Relinking with Forward-PR and Random Move
		PathRelinking PR(2,0);
		
		// make a new solution and Path-Relink it with the first solution in the pool
		p.RandomInit();
		FullEval(p);
		
		std::cout << "Current Solution: ";
		p.printSolution();
		p.printFitness();
		std::cout << std::endl;
		
		std::cout << "Starting of Path-Relinking with most diverse solution ..." << std::endl;
		
		PR(& p,Pool.GetMostDiverseSolution(p));
		
		std::cout << std::endl;
		
		std::cout << "Best Solution found: ";
		p.printSolution();
		p.printFitness();
		
		std::cout << "And After another Full Eval: " << std::endl;
		FullEval(p);
		p.printSolution();
		p.printFitness();
		
		
		std::cout << "Should solution be entered to Pool? " << std::endl;
		
		if (Pool.Add(p)) {
			std::cout << "YES, new Pool:" << std::endl;
			Pool.PrintPool();
		} else {
			std::cout << "NO, no better solution" << std::endl;
		}
		
	}	
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}