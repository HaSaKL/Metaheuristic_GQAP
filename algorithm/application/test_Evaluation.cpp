/* Test Program to Test if Evaluation Function is working properly */

#include <iostream>
#include <string>
#include <time.h>
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
		
		
		
		GQAP.GRASPInit(1);
		std::cout << "Initial GRASP ";
		GQAP.printSolution();
		
		GQAP.fullEvaluation();
		std::cout << "Fitness of GRASP Solution after FullEval: ";
		GQAP.printFitness();
		std::cout << std::endl << std::endl; 
		
		
		
		int maxTries = 10000000;
		std::cout << "Testing Random vs. GRASP with Alpha = 1 (Should be similar to random) vs. GRASP with Alpha = 0.4 and pure Greedy (Alpha = 0)" << std::endl;
		std::cout << "Doing " << maxTries << " runs." << std::endl << std::endl;
		
		double avgRandom = 0;
		double avgGRASPRandom = 0;
		double avgGreedy = 0;
		double avgGRASP  = 0;
		double solTime = 0;
		clock_t t;
		
		std::cout << "Testing Random Init: ..." << std::endl;
		t = clock();
		for (int i = 0; i < maxTries; i++) {
			GQAP.RandomInit();
			GQAP.fullEvaluation();
			avgRandom = avgRandom + GQAP.fitness() / maxTries;
		}
		t = clock() - t;
		std::cout << "Average Fitness: " << avgRandom << std::endl;
		std::cout << "Total Runtime: " << t * 1000 / (CLOCKS_PER_SEC) << " ms. ;  Avg. Runtime: " << (t * 1000000 / (CLOCKS_PER_SEC)) / maxTries << " µs" << std::endl<<std::endl; 
		
		
		std::cout << "Testing Random Init with GRASP: ..." << std::endl;
		t = clock();
		for (int i = 0; i < maxTries; i++) {
			GQAP.GRASPInit(1);
			GQAP.fullEvaluation();
			avgGRASPRandom = avgGRASPRandom + GQAP.fitness() / maxTries;
		}
		t = clock() - t;
		std::cout << "Average Fitness: " << avgGRASPRandom << std::endl;
		std::cout << "Total Runtime: " << t * 1000 / (CLOCKS_PER_SEC) << " ms. ;  Avg. Runtime: " << (t * 1000000 / (CLOCKS_PER_SEC)) / maxTries << " µs" << std::endl<<std::endl; 
		
		
		std::cout << "Testing GRASP-Init: ..." << std::endl;
		t = clock();
		for (int i = 0; i < maxTries; i++) {
			GQAP.GRASPInit(0.4);
			GQAP.fullEvaluation();
			avgGRASP = avgGRASP + GQAP.fitness() / maxTries;
		}
		t = clock() - t;
		std::cout << "Average Fitness: " << avgGRASP << std::endl;
		std::cout << "Total Runtime: " << t * 1000 / (CLOCKS_PER_SEC) << " ms. ;  Avg. Runtime: " << double((t * 1000000 / (CLOCKS_PER_SEC)) / maxTries) << " µs" << std::endl<<std::endl; 
		
		
		std::cout << "Testing Greedy Init: ..." << std::endl;
		t = clock();
		for (int i = 0; i < maxTries; i++) {
			GQAP.GRASPInit(0);
			GQAP.fullEvaluation();
			avgGreedy = avgGreedy + GQAP.fitness() / maxTries;
		}
		t = clock() - t;
		std::cout << "Average Fitness: " << avgGreedy << std::endl;
		std::cout << "Total Runtime: " << t * 1000 / (CLOCKS_PER_SEC) << " ms. ;  Avg. Runtime: " << (t * 1000000 / (CLOCKS_PER_SEC)) / maxTries << " µs" << std::endl<<std::endl; 
		//*/
	} 
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}