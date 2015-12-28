#include "GQAP_GRASP_Algo.h"

// C O N S T R U C T O R 

GQAP_GRASP_Algo::GQAP_GRASP_Algo(parameters _param) {
	
	// copy the parameters
	param = _param;
	
	// read the problem data and save an arbitrary solution as best
	p = new GQAP(param.problemFile);
	
	// initialize the best Solution to a random solution
	p->RandomInit();
	fullEval(*p);
	bestSol = *p;
	
	// Initialize the Incremental Evaluation Function
	incrEval = new GQAP_ElementFlip_IncrEval(*p);
	
	// Calculate Neighborhood Size
	NeighborhoodSize = p->GetNumEquip() * (p->GetNumLocation() - 1);
	
	// setup local search algorithm
	switch(param.LSStrategy) {
		case LSStrategyBestImprov:
			nh = new moOrderNeighborhood<GQAP_ElementFlipIndex_Neighbor>(NeighborhoodSize);
			ls = new moSimpleHC<GQAP_ElementFlipIndex_Neighbor>(*nh, fullEval, *incrEval);
			break;
			
		case LSStrategyRandomImprov:
			nh = new moRndWithoutReplNeighborhood<GQAP_ElementFlipIndex_Neighbor>(NeighborhoodSize);
			ls = new moFirstImprHC<GQAP_ElementFlipIndex_Neighbor>(*nh, fullEval, *incrEval);
			break;
			
		case LSStrategyNone:
			ls = new moDummyLS<GQAP_ElementFlipIndex_Neighbor>(fullEval);
			break;
	}
	
	// setup the continuator
	switch(param.stoppingCriterion) {
		case StoppingCriterionIterations:
			cont = new moIterContinuator<GQAP_ElementFlipIndex_Neighbor>(param.maxIterations);
			break;
		
		case StoppingCriterionRuntime:
			cont = new moTimeContinuator<GQAP_ElementFlipIndex_Neighbor>(param.maxRuntime);
			break;
			
		case StoppingCriterionValue:
			cont = new moFitContinuator<GQAP_ElementFlipIndex_Neighbor>(param.targetValue + pow(10,-6));
			// Note: Add a Small Epsilonn to compensate float-round-offs during incrEvals
			break;	
			
		case StoppingCriterionValueIterations:
			// Set Continuator to Iterations First and to Value after it has been found in the Time2Targer-Function
			cont = new moIterContinuator<GQAP_ElementFlipIndex_Neighbor>(param.maxIterations);
			break;
			
		case StoppingCriterionValueTime:
			// Set Continuator to Runtime First and to Value after it has been found in the Time2Targer-Function
			cont = new moTimeContinuator<GQAP_ElementFlipIndex_Neighbor>(param.maxRuntime);
			break;
	}
	
	// setup the alpha-generator
	switch(param.StartSol) {
		case StartSolGRASPFixed:
			alpha = new GRASP_FixedAlpha(param.fixedAlpha);
			break;
			
		case StartSolGRASPReactive:
			alpha = new GRASP_ReactiveAlpha(*p, param.maxAlpha, param.minAlpha, param.numAlpha, param.itsReCalcAlpha);
			break;
		
		case StartSolGRASPUniform:
			alpha = new GRASP_UniformRandomAlpha(param.maxAlpha, param.minAlpha, param.numAlpha);
			break;
		
		case StartSolGreedy:
			alpha = new GRASP_FixedAlpha(0);
			break;
		
		case StartSolRandom:
			alpha = new GRASP_FixedAlpha(1);
			break;
	}
	
	// FIXME: setup the path-relinking, don't forget the solution pool
}

GQAP_GRASP_Algo::~GQAP_GRASP_Algo() {
	delete p;
	delete incrEval;
	delete cont;
	delete nh;
	delete ls;
	delete alpha;
	
	//FIXME: delete the path relinking
}


// R U N N E R S

// Definition of a single Iteration of the GRASP-Algorithm
void GQAP_GRASP_Algo::GRASPIteration() {
	
	// Initialize the a Soluion
	p->GRASPInit(alpha->operator ()(*p));
	fullEval(*p);
	
	// Do the Local Search
	ls->operator ()(*p);
	
	// FIXME: Add the Path-Relinking!
}

// Silent run of the algorithm as defined in the parameters. Solution Values and Runtime are saved in the call parameters
void GQAP_GRASP_Algo::Run(GQAP_Solution & _Sol, double & _Runtime) {
	
	// save a random solution as the best solution
	GQAP_Solution tmpSol;
	
	// setup timers
	clock_t t;
	double elapsedTime;
	
	// init stopping criterion
	cont->init(*p);
	
	// init alpha generator
	alpha->init(*p);
	
	//start timer
	t = clock();
	
	// start the algorithm
	do {
		
		GRASPIteration();
		tmpSol = *p;
		
		if(tmpSol > bestSol) {
			bestSol = tmpSol;
		}
		
	} while(cont->operator ()(*p));
	
	// calculate running time in ms
	t = clock_t() - t;
	elapsedTime = double(t) *1000 / (CLOCKS_PER_SEC);
	
	// save results in function paramerters
	_Runtime = elapsedTime;
	_Sol = bestSol;
}
	
// noisy run of the algorithm (with some output)	
void GQAP_GRASP_Algo::Run() {
	double Runtime;
	GQAP_Solution Sol;
	
	Run(Sol, Runtime);
	
	// print result
	std::cout << "Solution Value: " << Sol.fitness() << ", Time: " << Runtime << std::endl;
}
	
// Implementation of time-to-target runs including the output format
void GQAP_GRASP_Algo::RunTimeToTarget() {
	
	// Initialize variables
	unsigned int itCounter = 0;		// counts iterations until target value has been found
	clock_t t;						// clock ticker
	double timeToTarget;			// holds runtime of singel t2t-runs
	
	// See if a target has to been found first
	// in this case the constructor did already set the valid 
	// stopping criterion. The value needs to be calculated and set as
	// new stopping criterion
	if ( (param.stoppingCriterion == StoppingCriterionValueIterations) || (param.stoppingCriterion == StoppingCriterionValueTime)) {
		
		// Announce Targte-value search
		std::cout << "Starting Time-To-Target Search without Target Value." << std::endl;
		std::cout << "Running GRASP for ";
		if (param.stoppingCriterion == StoppingCriterionValueIterations) {
			std::cout << param.maxIterations << " Iterations to Find a Target First ..." << std::endl;
 		} else {
			std::cout << param.maxRuntime << " Seconds to Find a Target First ..." << std::endl;
		}
		
		// Run Algorithm Once to find a Solution
		GQAP_Solution tmpSol;
		double tmpTime;
		Run(tmpSol, tmpTime);
		
		// delete the old continuator and set a new value continuator for time-to-target
		delete cont;
		cont = new moFitContinuator<GQAP_ElementFlipIndex_Neighbor>(tmpSol.fitness() + pow(10,-6));
		param.targetValue = tmpSol.fitness();
		
		// write result to output
		std::cout << "Target Value found! Using " << tmpSol.fitness() << " as Target Value " << std::endl;
	}
	
	// Open Output File and write header of results table if file is empty
	std::ofstream resultsFile;
	resultsFile.open(param.resultsFile.c_str(), std::ios::app);
	if (resultsFile.tellp() == 0) {	// if file is empty
		resultsFile << "Problem; StartSol; LSStrategy; PRMeth; PRDir; PRPoolSelect; Time; Iterations; Target; Result" << std::endl;
	}
	
	// Print header for console output
	std::cout << "Time; Iterations; Repetition" << std::endl;
	
	// do time-to-target runs for defined number of repetitions
	for (int i = 0; i < param.numRepetition; i++) {
		
		// (re-)initialize continuator and alpha-generator for next time-to-target run
		cont->init(*p);
		alpha->init(*p);
		
		// reset counter and start clock
		itCounter = 0;
		t = clock();
		
		// run time to target until target value has been found. No solution comparision needed
		// FIXME: If a better solution than target has been found: It should be saved!
		do {
			GRASPIteration();
			itCounter++;
		} while(cont->operator ()(*p));
		
		// calculate time-to-target in ms
		t = clock() - t;
		timeToTarget = double(t) * 1000 / (CLOCKS_PER_SEC);
		
		// print result
		std::cout << timeToTarget << " ms; \t " << itCounter << " iterations; \t repetition " << i << std::endl;
		
		// write results to file
		resultsFile << param.problemFile << "; " << int(param.StartSol) << "; " << int(param.LSStrategy)<< "; ";
		resultsFile << int(param.PRMeth) << "; " << int(param.PRDir) << "; " << int(param.PRPoolSelect) << "; ";
		resultsFile << timeToTarget << "; " << itCounter << "; ";
		resultsFile << param.targetValue << "; " << p->fitness() << "; " << std::endl;
	}
	
	// close results file
	resultsFile.close();
}


// S W I T C H E S

