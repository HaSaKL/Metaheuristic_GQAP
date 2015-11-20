/* Test Program to Test if Evaluation Function is working properly */

#include <iostream>
#include <string>
#include "GQAP.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "Metaheuristic for the GQAP compiled at " << __DATE__ << " " << __TIME__ << std::endl;
		std::cout << "Evauation and Initialization Function Test" << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
		
		std::cout << "Loading Problem \"";
		
		std::string fileName = "../../../test_instances/own_instances/mini_test_instances/4-2.txt";
		std::cout << fileName << "\"" << std::endl;
		
		GQAP GQAP(fileName);
		
		std::cout << "... done. " << std::endl << std::endl;
		
		
		
		std::cout << "Uninitialized ";
		GQAP.printSolution();
		
		GQAP.fullEvaluation();
		std::cout << "Initial Fitness: ";
		GQAP.printFitness();
		std::cout << std::endl << std::endl; 
		
		
		
		GQAP.RandomInit();
		std::cout << "Initial Random ";
		GQAP.printSolution();
		
		GQAP.fullEvaluation();
		std::cout << "Fitness of Random Solution:  ";
		GQAP.printFitness();
		std::cout << std::endl << std::endl; 
		
		
		
		GQAP.GRASPInit(0.2);
		std::cout << "Initial GRASP ";
		GQAP.printSolution();
		
		GQAP.fullEvaluation();
		std::cout << "Fitness of GRASP Solution after FullEval: ";
		GQAP.printFitness();
		std::cout << std::endl << std::endl; 
		
	} 
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}