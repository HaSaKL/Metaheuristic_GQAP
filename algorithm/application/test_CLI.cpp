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
		std::cout << "Output File name:     " << param.outputFile << std::endl << std::endl;
		
		std::cout << "Stopping Criterion:   " << param.stoppingCriterion << std::endl;
		std::cout << "Maximum Iteration:    " << param.maxIterations << std::endl;
		std::cout << "Maximum Runtime:      " << param.maxRuntime << std::endl;
		std::cout << "Target Value:         " << param.targetValue << std::endl << std::endl;
		
		std::cout << "Search Strategy:      " << param.LSStrategy << std::endl << std::endl;
		
		std::cout << "Solution Init Method: " << param.StartSol << std::endl;
		std::cout << "Fixed Alpha:          " << param.fixedAlpha << std::endl;
		std::cout << "min Alpha:            " << param.minAlpha << std::endl;
		std::cout << "max Alpha:            " << param.maxAlpha << std::endl;
		std::cout << "num Alpha:            " << param.numAlpha << std::endl;
		std::cout << "recalculation after:  " << param.itsReCalcAlpha << std::endl << std::endl;
		
		std::cout << "PR Direction:         " << param.PRDir << std::endl;
		std::cout << "PR Move Selector:     " << param.PRMeth << std::endl;
		std::cout << "PR Pool Size:         " << param.PRPoolSize << std::endl;
		std::cout << "PR Pool Selector:     " << param.PRPoolSelect << std::endl << std::endl;
		//*/
	} 
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}