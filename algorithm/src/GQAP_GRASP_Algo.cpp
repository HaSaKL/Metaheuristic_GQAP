#include "GQAP_GRASP_Algo.h"

// C O N S T R U C T O R 

GQAP_GRASP_Algo::GQAP_GRASP_Algo(parameters _param) {
	
	//std::cout << "DEBUG: Constuctor Called. Now inside Constructor." << std::endl;
	
	// copy the parameters
	param = _param;
	
	//std::cout << "DEBUG: Constructing Problem " << std::endl;
	
	// read the problem data and save an arbitrary solution as best
	p = new GQAP(param.problemFile);
	
	//std::cout << "DEBUG: Init best Solution " << std::endl;
	
	// initialize the best Solution to a random solution
	//std::cout << "DEBUG: Init Random Init p " << std::endl;
	p->RandomInit();
	//std::cout << "DEBUG: Full Eval p " << std::endl;
	fullEval(*p);
	//std::cout << "DEBUG: Assignment *p to randSol " << std::endl;
	randSol = p->GetSolution();
	//std::cout << "DEBUG: Assignment bestSol to randSol " << std::endl;
	bestSol = randSol;
	
	//std::cout << "DEBUG: Init incrEval " << std::endl;
	
	// Initialize the Incremental Evaluation Function
	incrEval = new GQAP_ElementFlip_IncrEval(*p);
	
	//std::cout << "DEBUG: Setting NH-Size " << std::endl;
	
	// Calculate Neighborhood Size
	NeighborhoodSize = p->GetNumEquip() * (p->GetNumLocation() - 1);
	
	//std::cout << "DEBUG: Init LS" << std::endl;
	
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
			nh = new moOrderNeighborhood<GQAP_ElementFlipIndex_Neighbor>(1);
			ls = new moDummyLS<GQAP_ElementFlipIndex_Neighbor>(fullEval);
			break;
	}
	
	//std::cout << "DEBUG: Init Continuator" << std::endl;
	
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
	
	//std::cout << "DEBUG: Init Alpha" << std::endl;
	 
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
	
	//std::cout << "DEBUG: Init Pool" << std::endl;
	
	Pool = new SolutionPool(param.PRPoolSize);
	
	if (param.PRMeth != PRMethNone) {
		//std::cout << "DEBUG: Init PR" << std::endl;
		PR = new PathRelinking(param.PRDir, param.PRMeth);
	}
}

GQAP_GRASP_Algo::~GQAP_GRASP_Algo() {
	delete p;
	delete incrEval;
	delete cont;
	delete nh;
	delete ls;
	delete alpha;
	
	delete Pool;
	
	// only delete pool parameters if they have been defined. Otherwise: segmentation fault
	if (param.PRMeth != PRMethNone) {
		delete PR;
	}
}


// R U N N E R S

// Definition of a single Iteration of the GRASP-Algorithm
void GQAP_GRASP_Algo::GRASPIteration() {
	
	// Initialize the a Soluion
	p->GRASPInit(alpha->operator ()(*p));
	fullEval(*p);
	
	// Do the Local Search
	ls->operator ()(*p);
	
	// Do the Path-Relining, if required
	if (param.PRMeth != PRMethNone) {
		
		// check if solution can be added to the pool
		// this will make sure, that the pool will be filled first
		bool addedToPool = Pool->Add(*p);
		
		// if not good enough for the pool, do the path relinking using PRPoolSelection Method provided by the parameter
		if (!addedToPool) {
			switch(param.PRPoolSelect) {
				case PRPoolSelectDiverse:
					// PR against the most diverse solution and try to add result
					PR->operator ()(p, Pool->GetMostDiverseSolution(*p));
					Pool->Add(*p);
					break;
					
				case PRPoolSelectRandom:
					// PR against a random solution from the pool and try to add result
					PR->operator ()(p, Pool->GetRandomSolution());
					Pool->Add(*p);
					break;
				
				case PRPoolSelectAll:
					// make a copy of the current solution
					GQAP_Solution currSol = p->GetSolution();
					
					// PR every solution in the pool against current solution and try to add the result
					for (int i = 0; i < Pool->GetSize(); i++) {
						*p = currSol;
						PR->operator ()(p, Pool->GetSolution(i));
						Pool->Add(*p);
					}
					
					break;
			}
		}
	}
}

// Silent run of the algorithm as defined in the parameters. Solution Values and Runtime are saved in the call parameters
void GQAP_GRASP_Algo::Run(GQAP_Solution & _Sol, double & _Runtime) {
	
	// save a random solution as the best solution in constructor. This can now be overwritten with tmpSol (currentSol)
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
		tmpSol = p->GetSolution();
		if(tmpSol > bestSol) {
			bestSol = tmpSol;
		}
		
	} while(cont->operator ()(*p));
	
	// calculate running time in ms
	t = clock_t() - t;
	elapsedTime = double(t) *1000 / (CLOCKS_PER_SEC);
	
	// check pool for best solution in case Path-Relinking was carried out
	if(param.PRMeth != PRMethNone) {
		tmpSol = Pool->GetBestSolution();
		if (tmpSol > bestSol) {
			bestSol = tmpSol;
		}
	}
	
	// save results in function paramerters
	_Runtime = elapsedTime;
	_Sol = bestSol;
	
	/*// DEBUG
	std::cout << "DEBUG: Results optained in Run(& _Sol, & _double)" << std::endl;
	std::cout << "Runtime: " << _Runtime << std::endl;
	_Sol.printFitness();
	_Sol.printSolution();
	
	std::cout << "DEBUG: Contents of tmpSol: " << std::endl;
	tmpSol.printFitness();
	tmpSol.printSolution();
	std::cout << "DEBUG: Exiting Run(& _Sol, & _double) " << std::endl;
	// */
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
			std::cout << param.maxIterations << " Iterations to find a Target Value ..." << std::endl;
 		} else {
			std::cout << param.maxRuntime << " Seconds to find a Target Value ..." << std::endl;
		}
		
		// Run Algorithm Once to find a Solution
		GQAP_Solution tmpSol;
		double tmpTime;
		rng.reseed(param.seed/2);
		
		/*// DEBUG
		std::cout << "Using Random Seed: " << param.seed << std::endl;
		std::cout << "Starting Run(tmpSol, tmpTime) " << std::endl;
		std::cout << "Initial Values for tmpSol: " << std::endl;
		tmpSol.printSolution();
		tmpSol.printFitness();
		//*/
		
		Run(tmpSol, tmpTime);
		
		/* // DEBUG
		std::cout << "DEBUG: Finished Intial Run in Time-to-Target Loop" << std::endl;
		std::cout << "DEBUG: Solution:" << std::endl;
		tmpSol.printFitness();
		tmpSol.printSolution();
		// */
		
		// delete the old continuator and set a new value continuator for time-to-target
		delete cont;
		cont = new moFitContinuator<GQAP_ElementFlipIndex_Neighbor>(tmpSol.fitness() + pow(10,-6));
		param.targetValue = tmpSol.fitness();
		
		// write result to output
		std::cout << "Target Value found! Using " << param.targetValue << " as Target Value " << std::endl;
	}
	
	
	// Open Output File and write header of results table if file is empty
	// std::cout << "DEBUG: Defining Reuslts File: " << std::endl;
	//std::cout << "DEBUG: Defining Reuslts File: " << std::endl;
	//std::cout << param.resultsFile.c_str() << std::endl;
	std::ofstream resultsFile;
	
	//std::cout << "DEBUG: Opening Results File" << std::endl;
	
	//resultsFile.open(param.resultsFile.c_str());
	resultsFile.open(param.resultsFile.c_str(), std::ofstream::out | std::ofstream::app);
	
	//std::cout << "DEBUG: Writing First Line if needed " << std::endl;
	if (resultsFile.tellp() == 0) {	// if file is empty
		resultsFile << "Problem; StartSol; LSStrategy; PRMeth; PRDir; PRPoolSelect; Time; Iterations; Target; Result" << std::endl;
	}
	
	
	// Reseed, so that results with same seed and value provided and not provided are better reproducebale
	// devide by to for reruns --> see EO RNG::RESEED documentation
	rng.reseed(param.seed/2);
	
	std::cout << "Using Random Seed: " << param.seed << std::endl;
	
	
	// Print header for console output
	std::cout << "Time; \t Iterations; \t Repetition" << std::endl;
	
	// do time-to-target runs for defined number of repetitions
	// std::cout << "DEBUG: Starting Time-To-Target Run " << std::endl;
	for (int i = 0; i < param.numRepetition; i++) {
		
		// (re-)initialize continuator and alpha-generator and empty pool for next time-to-target run
		cont->init(*p);
		alpha->init(*p);
		Pool->Clear();
		
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
		
		// get best result
		
		// print result
		std::cout << timeToTarget << " ms; \t " << itCounter << " iterations; \t repetition " << i << std::endl;
		
		// write results to file
		resultsFile << param.problemFile << "; " << int(param.StartSol) << "; " << int(param.LSStrategy)<< "; ";
		resultsFile << int(param.PRMeth) << "; " << int(param.PRDir) << "; " << int(param.PRPoolSelect) << "; ";
		resultsFile << timeToTarget << "; " << itCounter << "; ";
		resultsFile << param.targetValue << "; " << p->fitness() << "; " << std::endl;
	}
	
	// close results file
	// std::cout << "DEBUG: Closing File.";
	resultsFile.close();
}