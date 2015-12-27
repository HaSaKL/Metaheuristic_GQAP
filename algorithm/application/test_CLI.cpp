#include <iostream>
#include <string>
#include <eo>
#include "GQAP_CLI.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "Metaheuristic for the GQAP compiled at " << __DATE__ << " " << __TIME__ << std::endl;
		std::cout << "Test for CLI and CLI-Parser" << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
	
		// Initialize Parser and load parameters from CLI
		eoParser parser(argc, argv);
		parameters param;
		parseFile(parser, param);
		
		
		// Write all the Parameter values
		std::cout << "Random Seed:          " << param.seed << std::endl << std::endl;
		
		std::cout << "Problem File to load: " << param.problemFile << std::endl;
		std::cout << "Output File name:     " << param.resultsFile << std::endl << std::endl;
		
		std::cout << "Number of Repetions:  " << param.numRepetition << std::endl << std::endl;
		
		std::cout << "Stopping Criterion:   ";
		switch(param.stoppingCriterion) {
			case StoppingCriterionIterations:
				std::cout << "Number of Iterations"<< std::endl;
				std::cout << "Maximum Iteration:    " << param.maxIterations << std::endl;
				break;
			case StoppingCriterionRuntime:
				std::cout << "Runtime"<< std::endl;
				std::cout << "Maximum Runtime:      " << param.maxRuntime << std::endl;
				break;	
			case StoppingCriterionValue:
				std::cout << "Target Value"<< std::endl;
				std::cout << "Target Value:         " << param.targetValue << std::endl;
				break;	
			case StoppingCriterionValueIterations:
				std::cout << "Target Value after Target Value Search for a given Iteration Number"<< std::endl;
				std::cout << "Maximum Iteration:    " << param.maxIterations << std::endl;
				break;		
			case StoppingCriterionValueTime:
				std::cout << "Target Value after Target Value Search for a given Runtime"<< std::endl;
				std::cout << "Maximum Runtime:      " << param.maxRuntime << std::endl;
				break;			
				
		}
		std::cout << std::endl;
		
		std::cout << "Search Strategy:      ";
		switch(param.LSStrategy) {
			case LSStrategyBestImprov:
				std::cout << "Best Improvement";
				break;
			case LSStrategyRandomImprov:
				std::cout << "Random Improvement";
				break;
			case LSStrategyNone:
				std::cout << "No Local Search";
				break;
		}
		std::cout << std::endl << std::endl;
		
		std::cout << "Solution Init Method: ";
		switch(param.StartSol) {
			case StartSolGRASPFixed:
				std::cout << "GRASP with Fixed Alpha" << std::endl;
				std::cout << "Fixed Alpha:          " << param.fixedAlpha << std::endl;
				break;
			case StartSolGRASPReactive:
				std::cout << "GRASP with Reactive Alpha" << std::endl;
				std::cout << "min Alpha:            " << param.minAlpha << std::endl;
				std::cout << "max Alpha:            " << param.maxAlpha << std::endl;
				std::cout << "num Alpha:            " << param.numAlpha << std::endl;
				std::cout << "recalculation after:  " << param.itsReCalcAlpha << std::endl << std::endl;
				break;
			case StartSolGRASPUniform:
				std::cout << "GRASP with Uniform Random Alpha" << std::endl;
				std::cout << "min Alpha:            " << param.minAlpha << std::endl;
				std::cout << "max Alpha:            " << param.maxAlpha << std::endl;
				std::cout << "num Alpha:            " << param.numAlpha << std::endl;
				break;
			case StartSolGreedy:
				std::cout << "Greedy" << std::endl;
				break;
			case StartSolRandom:
				std::cout << "Random" << std::endl;
				break;
		}
		std::cout << std::endl;
		
		std::cout << "PR Move Selector:     ";
		switch(param.PRMeth) {
			case PRMethNone:
				std::cout << "No Path-Relinking" << std::endl;
				break;
			case PRMethGRASP:
				std::cout << "GRASP Move Selector" << std::endl;
				break;
			case PRMethGreedy:
				std::cout << "Greedy Move Selector" << std::endl;
				break;	
			case PRMethRandom:
				std::cout << "Random Move Selector" << std::endl;
				break;
		}
	
		if(param.PRMeth != PRMethNone) {
			
			std::cout << "PR Direction:         ";
			switch(param.PRDir) {
				case PRDirBackward:
					std::cout << "backward" << std::endl;
					break;
				case PRDirForward:
					std::cout << "backward" << std::endl;
					break;
				case PRDirMixed:
					std::cout << "forward-backward (mixed)" << std::endl;
					break;	
			}
			std::cout << "PR Pool Size:         " << param.PRPoolSize << std::endl;
			std::cout << "PR Pool Selector:     ";
			switch(param.PRPoolSelect) {
				case PRPoolSelectAll:
					std::cout << "All Solution in the Pool" << std::endl;
					break;
				case PRPoolSelectDiverse:
					std::cout << "Most Diverse Solution in Pool" << std::endl;
					break;
				case PRPoolSelectRandom:
					std::cout << "Random Solution from Pool" << std::endl;
					break;	
			}
		}
	} 
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}