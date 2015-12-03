#include <iostream>
#include <string>

// neede eo headers
#include <eo>
#include <neighborhood/moOrderNeighborhood.h>

// Problem Specific headers
#include "GQAP.h"
#include "GQAP_Eval.h"
#include "SolutionPool.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "Metaheuristic for the GQAP compiled at " << __DATE__ << " " << __TIME__ << std::endl;
		std::cout << "ElementFlip-Neighborhood Test" << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
		
		std::cout << "Loading Problem \"";
		
		std::string fileName = "../../../test_instances/own_instances/mini_test_instances/4-2.txt";
		std::cout << fileName << "\"" << std::endl;
		
		// Initialize Problem
		GQAP p(fileName);
		std::cout << "... done. " << std::endl << std::endl;
		
		// Define problem functions for cleaner code
		GQAP_Eval FullEval;
		
		// Define a solution pool
		int PoolSize = 3;
		SolutionPool Pool(PoolSize);
		
		
		// Fill the Pool with random solution until it is full
		bool returnValue;
		for (int i = 0; i < 2 * PoolSize; i++) {
			p.RandomInit();
			FullEval(p);
			
			std::cout << "Trying to add ";
			p.printSolution();
			std::cout << " with Fitness " << p.fitness();
			
			returnValue = Pool.Add(p);
			
			if (returnValue) {
				std::cout << "... added to Pool." << std::endl << std::endl;
			} else {
				std::cout << "... not added to Pool." << std::endl << std::endl;
			}
			
			Pool.PrintPool();
			std::cout << std::endl << std::endl;
		}
		
		
	}
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}