// stdlib headers
#include <iostream>
#include <string>

// neede eo headers
#include <eo>
#include <neighborhood/moRndWithoutReplNeighborhood.h>
#include <algo/moFirstImprHC.h>
#include <algo/moRandomBestHC.h>
#include <algo/moSimpleHC.h>
#include <algo/moNeutralHC.h>

// Problem Specific headers
#include "GQAP.h"
#include "GQAP_Eval.h"
#include "GQAP_ElementFlip_Neighbor.h"
#include "GQAP_ElementFlip_IncrEval.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "Metaheuristic for the GQAP compiled at " << __DATE__ << " " << __TIME__ << std::endl;
		std::cout << "ElementFlip-Neighborhood Test with Hill-Climbing Heuristic" << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
		
		//std::string fileName = "../../../test_instances/own_instances/mini_test_instances/4-2.txt";
		std::string fileName = "../../../test_instances/from_literature/original_format/cordeau/50-10-95.txt";
		int tmp = fileName.find_last_of("/") + 1;
		std::cout << "Using Problem " <<  fileName.substr(tmp)<< std::endl << std::endl;
		
		// Initialize Problem
		GQAP p(fileName);
		
		// Define problem functions for cleaner code
		GQAP_Eval FullEval;
		
		// Define Neighbor and its Evaluation
		int NeighborhoodSize = p.GetNumEquip() * (p.GetNumLocation() - 1);
		std::cout << "Neighborhood Size = " << NeighborhoodSize << std::endl;
		GQAP_ElementFlipIndex_Neighbor n1;
		GQAP_ElementFlip_IncrEval IncrEval(p);
		
		// define neighborhood
		moRndWithoutReplNeighborhood<GQAP_ElementFlipIndex_Neighbor> nh_Flip(NeighborhoodSize);
		
		// define heuristics
		moRandomBestHC<GQAP_ElementFlipIndex_Neighbor> HC_Algo_Random(nh_Flip, FullEval, IncrEval);
		moFirstImprHC<GQAP_ElementFlipIndex_Neighbor> HC_Algo_First(nh_Flip, FullEval, IncrEval);
		moNeutralHC<GQAP_ElementFlipIndex_Neighbor> HC_Algo_Neutral(nh_Flip, FullEval, IncrEval, NeighborhoodSize * 10);
		
		
		// do the search
		clock_t t;
		
		int maxIt = 1000;
		p.RandomInit();
		FullEval(p);
		double bestSol = p.fitness();
		double currSol = bestSol;
		
		std::cout << "Starting search, best known solution using Random Best HC with Random NH: " << bestSol << std::endl;
		
		t = clock();
		for (int i = 0; i < maxIt; i++) {
			//std::cout << i << ": ";
			
			// Initialize Solution Randomly
			p.RandomInit();
			FullEval(p);
		
			// Improve Soluition using HC-Algorithm
			HC_Algo_Random(p);
			
			currSol = p.fitness();
			
			//std::cout << currSol << std::endl;
			
			// Check if new best sol has been found
			if (currSol < bestSol) {
				bestSol = currSol;
				std::cout << "New Best Solution found in Iteration " << i << ": " << bestSol << std::endl;
			}
		}
		
		t = clock() - t;
		std::cout << "Finished all " << maxIt << " Iterations in " << double(t) * 1000 / (CLOCKS_PER_SEC) << " ms" << std::endl;
		std::cout << "Best Solution found: " << bestSol << std::endl;
		
		
		
		maxIt = 1000;
		p.RandomInit();
		FullEval(p);
		bestSol = p.fitness();
		currSol = bestSol;
		
		std::cout << "Starting search, best known solution using First Best HC with Random NH: " << bestSol << std::endl;
		
		t = clock();
		for (int i = 0; i < maxIt; i++) {
			//std::cout << i << ": ";
			
			// Initialize Solution Randomly
			p.RandomInit();
			FullEval(p);
		
			// Improve Soluition using HC-Algorithm
			HC_Algo_First(p);
			
			currSol = p.fitness();
			
			//std::cout << currSol << std::endl;
			
			// Check if new best sol has been found
			if (currSol < bestSol) {
				bestSol = currSol;
				std::cout << "New Best Solution found in Iteration " << i << ": " << bestSol << std::endl;
			}
		}
		
		t = clock() - t;
		std::cout << "Finished all " << maxIt << " Iterations in " << double(t) * 1000 / (CLOCKS_PER_SEC) << " ms" << std::endl;
		std::cout << "Best Solution found: " << bestSol << std::endl;
		
		
		
		maxIt = 1000;
		p.RandomInit();
		FullEval(p);
		bestSol = p.fitness();
		currSol = bestSol;
		
		std::cout << "Starting search, best known solution using Neutral HC with Random NH: " << bestSol << std::endl;
		
		t = clock();
		for (int i = 0; i < maxIt; i++) {
			//std::cout << i << ": ";
			
			// Initialize Solution Randomly
			p.RandomInit();
			FullEval(p);
		
			// Improve Soluition using HC-Algorithm
			HC_Algo_Neutral(p);
			
			currSol = p.fitness();
			
			//std::cout << currSol << std::endl;
			
			// Check if new best sol has been found
			if (currSol < bestSol) {
				bestSol = currSol;
				std::cout << "New Best Solution found in Iteration " << i << ": " << bestSol << std::endl;
			}
		}
		
		t = clock() - t;
		std::cout << "Finished all " << maxIt << " Iterations in " << double(t) * 1000 / (CLOCKS_PER_SEC) << " ms" << std::endl;
		std::cout << "Best Solution found: " << bestSol << std::endl;
	}
	catch(std::exception& e) {
		std::cout << "EXCEPTION COUGHT: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}