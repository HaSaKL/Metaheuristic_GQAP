#include <iostream>
#include <eo>
#include "GQAP_GRASP_Algo.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "GRASP Solver for the GQAP" << std::endl;
		std::cout << "compiled at " << __DATE__ << " " << __TIME__ << std::endl;
		std::cout << "Programming by Hagen Salewski (salewski@wiwi.uni-kl.de), University of Kaiserslautern" << std::endl << std::endl;
	
		// Initialize Parser, load and parse parameters from the CLI
		eoParser parser(argc, argv);
		parameters param;
		parseFile(parser, param);
		
		// Initialize the RNG with the provided seed
		rng.reseed(param.seed);
		
		std::cout << "Solving Problem: " << param.problemFile << std::endl << std::endl;
		
		// check if parameters are set to target value or if one should be found first
		switch(param.stoppingCriterion) {
			case StoppingCriterionValue:
			case StoppingCriterionValueIterations:
			case StoppingCriterionValueTime:
				break;
			default:
				throw std::runtime_error("ERROR. Time2Target-Algorithm: No Target Value or no Valid Combination of Stopping Criterions provided");
		}
		
		//std::cout << "DEBUG: Calling Algorithm Constructor " << std::endl;
		
		// Initialize the Algorithm
		GQAP_GRASP_Algo grasp(param);
		
		//std::cout << "DEBUG: Calling Time-to-Target-Method " << std::endl;
		
		grasp.RunTimeToTarget();
	} 
	
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}