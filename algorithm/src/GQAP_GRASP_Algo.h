#ifndef GQAP_GRASP_Algo_H
#define GQAP_GRASP_Algo_H

// solution and problem representation and evaluation functions
#include "GQAP_Solution.h"
#include "GQAP.h"
#include "GQAP_Eval.h"
#include "GQAP_ElementFlip_IncrEval.h"

// command line interface and constants
#include "GQAP_CLI.h"

// neighborhood
#include "GQAP_ElementFlip_Neighbor.h"

// possible neighborhood and local search definitions
#include <neighborhood/moOrderNeighborhood.h>
#include <neighborhood/moRndWithoutReplNeighborhood.h>
#include <neighborhood/moDummyNeighborhood.h>

#include <algo/moSimpleHC.h>
#include <algo/moFirstImprHC.h>
#include <algo/moDummyLS.h>

// possible stopping criteria
#include <continuator/moTimeContinuator.h>
#include <continuator/moFitContinuator.h>
#include <continuator/moIterContinuator.h>

// possible alpha generators
#include "GRASP_FixedAlpha.h"
#include "GRASP_ReactiveAlpha.h"
#include "GRASP_UniformRandomAlpha.h" 

// Solution Pool and Path-Relinking Classes
#include "PathRelinking.h"
#include "SolutionPool.h"

// for time measurement
#include <time.h>

// for results file handling
#include <fstream>

// implementation of an abstract GRASP Algorithm which uses the parameters set by the CLI
// this makes every part optional / modular: initialization is the only thing required and could be random
// local search an path-relinking are optional 
class GQAP_GRASP_Algo {
private:
	// a copy of the parameters
	parameters param;
	
	// the problem
	GQAP * p;
	
	// strcuture for the best known solution
	GQAP_Solution bestSol;
	GQAP_Solution randSol;
	
	// Neighborhood Size
	unsigned NeighborhoodSize;
	
	// Evaluation Function
	GQAP_Eval fullEval;
	GQAP_ElementFlip_IncrEval * incrEval;
	
	// a pointer to the local search function
	moLocalSearch<GQAP_ElementFlipIndex_Neighbor> * ls;
	
	// a pointer to the neighboorhood definition
	moIndexNeighborhood<GQAP_ElementFlipIndex_Neighbor> * nh;
	
	// a pointer to the continuator (stopping criterion)
	moContinuator<GQAP_ElementFlipIndex_Neighbor> * cont;
	
	// a pointer to an alpha-generator
	GRASP_Alpha * alpha;

	// a pointer to the solution pool
	SolutionPool * Pool;
	
	// a pointer to the Path-Relinking procedure
	PathRelinking * PR;
	
public:
	// Constructors
	GQAP_GRASP_Algo(parameters _param);
	~GQAP_GRASP_Algo();
	
	// Runners
	void Run(GQAP_Solution & _Sol, double & _Runtime);
	void Run();
	void RunTimeToTarget();
	void GRASPIteration();
};

#endif // GQAP_GRASP_Algo_H
