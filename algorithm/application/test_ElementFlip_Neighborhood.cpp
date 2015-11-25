// stdlib headers
#include <iostream>
#include <string>

// neede eo headers
#include <eo>
#include <neighborhood/moOrderNeighborhood.h>

// Problem Specific headers
#include "GQAP.h"
#include "GQAP_Eval.h"
#include "GQAP_ElementFlip_Neighbor.h"
#include "GQAP_ElementFlip_IncrEval.h"

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
		
		
		std::cout << "Initial Solution and Fitness: ";
		p.RandomInit();
		FullEval(p);
		p.printSolution();
		p.printFitness();
		std::cout << std::endl << std::endl;
		
		
		// Calculate Neighborhood Size -> for FlipNeighborhood: NumEquip * (NumLocation -1);
		int NeighborhoodSize = p.GetNumEquip() * (p.GetNumLocation() - 1);
		std::cout << "Neighborhood Size = " << NeighborhoodSize << std::endl;
		
		//  Declare Neighbor and Neighborhood and Incremental Evalutation
		GQAP_ElementFlipIndex_Neighbor n1;
		moOrderNeighborhood<GQAP_ElementFlipIndex_Neighbor> nh_Flip(NeighborhoodSize);
		GQAP_ElementFlip_IncrEval IncrEval(p);
		
		// Initialize Neighborhood
		nh_Flip.init(p,n1);

		std::cout << "Position: " << nh_Flip.position() << std::endl;
		IncrEval(p,n1);
		std::cout << "Fitness of neighbor: " << n1.fitness() << std::endl;		
		std::cout << "has another Neighbor: " << nh_Flip.hasNeighbor(p) << std::endl << std::endl;
	
		/*while(nh_Flip.cont(p)) {
			nh_Flip.next(p,n1);
			std::cout << "Position: " << nh_Flip.position() << std::endl;
			IncrEval(p,n1);
			std::cout << "Fitness of neighbor: " << n1.fitness() << std::endl;		
			std::cout << "has another Neighbor: " << nh_Flip.cont(p) << std::endl << std::endl;
		}
		//*/
	}
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}