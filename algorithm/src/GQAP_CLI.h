/* This source file descripes the parameters and default values
 * which make up the command line interface to the GRASP implementation
 * */
#ifndef GQAP_CLI_H
#define GQAP_CLI_H

#include <eo>


// DEFINITION OF CONSTANTS FOR DIFFERENT ALGORITHM CONFIGURATIONS

// RUNTIME / STOPPING BEHAVIOUR
static const int StoppingCriterionIterations = 0;		// Stop the Algorithm after a given number of Iterations
static const int StoppingCriterionRuntime = 1;			// Stop the Algorithm after a given number of seconds
static const int StoppingCriterionValue = 2;			// Stop the Algorithm if at least the given value has been found
static const int StoppingCriterionValueTime = 3;		// First Run the Algortihm for a given time, the stop the Algorithm if at least the best value during that has beed found during those itertions has been found
static const int StoppingCriterionValueIterations = 4;	// First Run the Algorithm for a given number of iterations, then stop the algorithm if least the best value during that time has been found


// LOCAL SEARCH PHASE
static const int LSStrategyBestImprov   = 0;	// During LS Select best Neighbor in Neighborhood
static const int LSStrategyRandomImprov = 1;	// Randomly search Neighhood and select First Improvement
static const int LSStrategyNone			= 2;	// Skip the Local Search

// CONSTRUCTION PHASE
static const int StartSolRandom 	   = 0;		// Pure Random Construction of Initial Solution
static const int StartSolGreedy 	   = 1;		// Pure Greedy Construction of Initial Solution
static const int StartSolGRASPFixed    = 2;		// GRASP-Construction with Fixed Alpha Value
static const int StartSolGRASPReactive = 3;		// GRASP-Construction with Reactive Alpha Values
static const int StartSolGRASPUniform  = 4;		// GRASP-Construction with Random Alpha and Uniform Alpha-Value Distribution


// PATH-RELINKING PHASE - Direction
static const int PRDirForward 	= 0;	// Forward PR
static const int PRDirBackward 	= 1;	// Backward PR
static const int PRDirMixed 	= 2;	// alternting Forward and Backward PR
	
// PATH-RELINKING PHASE - Move Selection	
static const int PRMethRandom = 0;		// Random Move during PR
static const int PRMethGreedy = 1;		// Move with least worsening / best improvement
static const int PRMethGRASP  = 2;		// GRASP Move Selection based on GRASP settings
static const int PRMethNone   = 3;		// Skip Path-Relinking

// PATH-RELINKIN PHASE  - Pool Selection
static const int PRPoolSelectDiverse = 0;	// Select Most Diverse Solution for PR
static const int PRPoolSelectRandom  = 1;	// Select Random Solution for PR
static const int PRPoolSelectAll     = 2;	// Do PR with all Solutions in the Pool


struct parameters {
	// Radnom seed
	unsigned seed;
	
	// Problem description
	std::string problemFile;
	
	// Output File
	std::string outputFile;
	
	
	// Status File
	std::string statusFile;
	
	// local search Algorithm selection
	// 'b' - Best Improvement
	// 'f' - First Random Improvement
	// 'n' - No Local Search for Improvement
	char LSStrategy;
	
	
	// Stopping Criterion, if more than one is provided
	// 'i' - Number of Iterations
	// 't' - Time to Target 
	// 'T' - Max Runtime
	char stoppingCriterion;
	
	// Maximum number of Iterations
	unsigned int maxIterations;
	
	// Maximum Runtime in seconds
	unsigned int maxRuntime;
	
	// target value to hit
	double targetValue;
	
	
	// num repetition of experiments
	unsigned int numRepetition;
	
	
	// Selection of Alpha Value for Initialization
	// 'r' - Random Initialization
	// 'g' - Greedy Initialization
	// 'f' - GRASP with fixed Alpha Value
	// 'R' - GRASP Initialization with Reactive Alpha Value
	// 'U' - GRASP with Uniformly Distributed Alpha
	char StartSol;
	
	// fixed alpha value if given
	double fixedAlpha;
	
	// minimum Alpha Value for Random and Reactive Alpha for GRASP
	double minAlpha;
	
	// maximum Alpha Value for Random and Reactive Alpha for GRASP
	double maxAlpha;
	
	// Number of different Alpha Values for Random and Reactive Alpha for GRASP
	int numAlpha;
	
	// Number of Iterations after which Alpha Value Probabilities Should be Recalculated for Reactive GRASP
	int itsReCalcAlpha;
	
	
	// Selection of Path-Relinking Direction
	// 'f' - Forward Path-Relinking
	// 'b' - Backward Path-Relinking
	// 'm' - Mixed Path-Relinking
	char PRDir;
	
	
	// Selection of Move Selector for Path-Relinking
	// 'r' - Random Move Selector
	// 'g' - Greedy Move Selector
	// 'G' - GRASP Move Selector
	// FIXME: Here is is assumed, that if the GRASP Selector is choosen, it will be the same as for the Starting Sol! -> else add a Parameter
	char PRMeth;
	
	
	// Number of Elite Solutions in the Pool
	int PRPoolSize;
	
	
	// Selection of Solution agains which Path-Relinking Should be Run
	// 'r' - Select a Random Solution
	// 'd' - Select most diverse Solution
	// 'a' - do Path-Relinking versus all Solutions in the Pool
	char PRPoolSelect;
};


inline void parseFile(eoParser & parser, parameters & param) {

	// define the parameter, read it through the parser, and assign default values to it
	std::string str_status = parser.ProgramName() + ".status";
	eoValueParam<std::string> statusParam(str_status.c_str(), "status","Status file",'S');
	parser.processParam(statusParam, "Persistence");
	param.statusFile = statusParam.value();
	
	
	eoValueParam<unsigned> seed(unsigned(time(0)), 
		"seed", 
		"Random Number Seed", 
		'R');
	parser.processParam(seed, "Runtime");
	param.seed = seed.value(); 
	
	
	eoValueParam<std::string> problemFile("",
		"problemFile",
		"Path to problem file",
		'p',
		true);
	parser.processParam(problemFile, "IO");
	param.problemFile = problemFile.value();
	
	eoValueParam<std::string> outputFile(std::string("output.csv"),
		"resultsFile",
		"Path to the results output file",
		'o');
	parser.processParam(outputFile, "IO");
	param.outputFile = outputFile.value();
		
		
	eoValueParam<char> stoppingCriterion('i',
		"stoppingCriterion",
		"Stopping Criterion", 
		's',
		true);
	parser.processParam(stoppingCriterion, "Runtime");
	
		
	eoValueParam<unsigned> maxRuntime(0,
		"maxTime",
		"maximum Runtime in seconds",
		'T');
	parser.processParam(maxRuntime, "Runtime");
		
	eoValueParam<unsigned> maxIterations(0,
		"maxIter",
		"maximum number of iterations",
		'i');
	parser.processParam(maxIterations, "Runtime");
	
	eoValueParam<double> targetValue (std::numeric_limits<double>::max(), 
		"targetValue",
		"target objective value to stop at",
		'v');
	parser.processParam(targetValue, "Runtime");
		
		
	eoValueParam<unsigned> numRepetitions(1,
		"numRepetitions",
		"Number of Repetitions of Trys",
		'r');
	parser.processParam(numRepetitions, "Runtime");
	param.numRepetition = numRepetitions.value();
	
	
	eoValueParam<char> LSStrategy ('f',
		"LSStrategy",
		"Strategy of the Local Search",
		'l',
		true);
	parser.processParam(LSStrategy, "Local-Search");
	
	
	eoValueParam<char> StartSol('r',
		"StartSol",
		"Initialization Method",
		'a',
		true);
	parser.processParam(StartSol, "Construction");
	
		
	eoValueParam<double> fixedAlpha(0.2,
		"fixedAlpha",
		"Fixed Alpha Value",
		'f');
	parser.processParam(fixedAlpha, "Construction");
	
	eoValueParam<double>minAlpha (0,
		"minAlpha",
		"Minimum Alpha @ Initalization",
		'm');
	parser.processParam(minAlpha, "Construction");
		
	eoValueParam<double>maxAlpha (1,
		"maxAlpha",
		"Maximum Alpha @ Initalization",
		'M');
	parser.processParam(maxAlpha, "Construction");
		
	eoValueParam<double> numAlpha(10,
		"numAlpha",
		"Number of different Alpha Values @ Initialization",
		'n');
	parser.processParam(numAlpha, "Construction");
		
	eoValueParam<int> itsReCalcAlpha(100,
		"itsReCalcAlpha",
		"Iterations before New Alpha Probabilties are Calculated for Reacteve GRASP",
		'I');
	parser.processParam(itsReCalcAlpha, "Construction");
		
		
	eoValueParam<char> PRDir('f',
		"PRDir",
		"Direction of Path-Relinking",
		'd');
	parser.processParam(PRDir, "Path-Relinking");
	
	eoValueParam<char> PRMeth('r',	
		"PRMeth",
		"Move Selector for Path-Relinking",
		'm',
		true);
	parser.processParam(PRMeth, "Path-Relinking");
		
	eoValueParam<int> PRPoolSize (10,
		"PRPoolSize",
		"Size of the Elite Solution Set for Path-Relinking",
		'P');
	parser.processParam(PRPoolSize, "Path-Relinking");
	param.PRPoolSize = PRPoolSize.value();
		
	eoValueParam<char> PRPoolSelect ('r',
		"PRPoolSelect",
		"Method of Selection from Pool for Path-Relinking",
		'M');
	parser.processParam(PRPoolSelect,"Path-Relinkin");
	
	
	// CHECK IF PARAMETERS ARE SET CORRECTLY
	
	if (parser.userNeedsHelp()) {
		parser.printHelp(std::cout);
		exit(1);
	}
				
	if (statusParam.value() != "") {
		std::ofstream os(statusParam.value().c_str());
		os << parser;
	}
	
	switch (stoppingCriterion.value()) {
		case 'i': 
			if (!parser.isItThere(maxIterations)) {
				throw std::runtime_error("ERROR: You need to set the maximum number of Iterations.");
			}
			param.stoppingCriterion = StoppingCriterionIterations;
			param.maxIterations = maxIterations.value();
			break;
			
		
		case 'v': 
			if (!parser.isItThere(targetValue)) {
				throw std::runtime_error("ERROR: You need to set a target value to run time-to-targer for.");
			}
			param.stoppingCriterion = StoppingCriterionValue;
			param.targetValue = targetValue.value();
			break;
		
		case 'T': 
			if (!parser.isItThere(maxRuntime)) {
				throw std::runtime_error("ERROR: You need to set a Maximum Runtime.");
			}
			param.stoppingCriterion = StoppingCriterionRuntime;
			param.maxRuntime = maxRuntime.value();
			break;
			
		case 'V':
			if (!parser.isItThere(maxRuntime)) {
				throw std::runtime_error("ERROR: You need to set a Maximum Runtime for the Target Value Search.");
			}
			if (!parser.isItThere(numRepetitions)) {
				throw std::runtime_error("ERROR: You need to set the number of Repetitions for the Time-To-Target Search");
			}
			param.stoppingCriterion = StoppingCriterionValueTime;
			param.maxRuntime = maxRuntime.value();
			break;
			
		case 'I':
			if (!parser.isItThere(maxIterations)) {
				throw std::runtime_error("ERROR: You need to set a Maximmum Nummber of Iterations for the Target Value Search");
			}
			if (!parser.isItThere(numRepetitions)) {
				throw std::runtime_error("ERROR: You need to set the number of Repetitions for the Time-To-Target Search");
			}
			param.stoppingCriterion = StoppingCriterionValueIterations;
			param.maxIterations = maxIterations.value();
			break;
		
		default:
			throw std::runtime_error("ERROR: stopping Criterion unknown");
	}

	switch (LSStrategy.value()) {
		case 'b':
			param.LSStrategy = LSStrategyBestImprov;
			break;
			
		case 'f':
			param.LSStrategy = LSStrategyRandomImprov;
			break;	
			
		case 'n':
			param.LSStrategy = LSStrategyNone;
			break;
			
		default:
			throw std::runtime_error("ERROR: Please specify the Local Search Strategy.");
	}
	
	switch (StartSol.value()) {
		case 'r':
			param.StartSol = StartSolRandom;
			break;
		
		case 'g':
			param.StartSol = StartSolGreedy;
			break;
			
		case 'f':
			if (!parser.isItThere(fixedAlpha)) {
				throw std::runtime_error("ERROR: You need to specify a fixed Alpha Value!");
			}
			param.StartSol = StartSolGRASPFixed;
			if ((fixedAlpha.value() < 0) || (fixedAlpha.value() > 1) ) {
				throw std::runtime_error("ERROR: Fixed Alpha Value should be between 0 and 1");
			}
			param.fixedAlpha = fixedAlpha.value();
			break;
			
		case 'R':
			if ( (!parser.isItThere(minAlpha)) || (!parser.isItThere(maxAlpha)) || (!parser.isItThere(numAlpha)) || (!parser.isItThere(itsReCalcAlpha))) {
				throw std::runtime_error("ERROR: You need to specify the Minimmum and Maximum Alpha Values and the Number of Different Alpha Values to Draw from. ");
			}
			param.StartSol = StartSolGRASPReactive;
			if ((minAlpha.value() > 1) || (minAlpha.value() < 0)) {
				throw std::runtime_error("ERROR: Minimum Alpha should be smaller the 1 and greater or equal to 0");
			}
			param.minAlpha = minAlpha.value();
			if ((maxAlpha.value() > 1) || (maxAlpha.value() < 0) || (maxAlpha.value() < minAlpha.value())) {
				throw std::runtime_error("ERROR: Maximum Alpha should be larger then Minimum Alpha and between zero and one");
			}
			param.maxAlpha = maxAlpha.value();
			if (numAlpha.value() >= 1) {
				throw std::runtime_error("ERROR: Number of different Alphase should at least be 1");
			}
			param.numAlpha = numAlpha.value();
			if (itsReCalcAlpha.value() >= 1) {
				throw std::runtime_error("ERROR: Number Iterations to Alpha-Probability Recalculation should at least be 1");
			}
			param.itsReCalcAlpha = itsReCalcAlpha.value();
			break;
			
		case 'U':
			if ((!parser.isItThere(minAlpha)) || (!parser.isItThere(maxAlpha)) || (!parser.isItThere(numAlpha))) {
				throw std::runtime_error("ERROR: You need to specify the Minimmum and Maximum Alpha Values and the Number of Different Alpha Values to Draw from. ");
			}
			param.StartSol = StartSolGRASPUniform;
			if ((minAlpha.value() > 1) || (minAlpha.value() < 0)) {
				throw std::runtime_error("ERROR: Minimum Alpha should be smaller the 1 and greater or equal to 0");
			}
			param.minAlpha = minAlpha.value();
			if ((maxAlpha.value() > 1) || (maxAlpha.value() < 0) || (maxAlpha.value() < minAlpha.value())) {
				throw std::runtime_error("ERROR: Maximum Alpha should be larger then Minimum Alpha and between zero and one");
			}
			param.maxAlpha = maxAlpha.value();
			if (numAlpha.value() >= 1) {
				throw std::runtime_error("ERROR: Number of different Alphase should at least be 1");
			}
			param.numAlpha = numAlpha.value();
			break;
		
		default:
			throw std::runtime_error("ERROR: Please specify the Intitialization Procedure.");
	}
	
	switch (PRMeth.value()) {
		case 'r':
			if (!parser.isItThere(PRDir)) {
				throw std::runtime_error("ERROR: Please specify a Path-Relinking Direction as well!");
			}
			param.PRMeth = PRMethRandom;
			break;
			
		case 'g':
			if (!parser.isItThere(PRDir)) {
				throw std::runtime_error("ERROR: Please specify a Path-Relinking Direction as well!");
			}
			param.PRMeth = PRMethGreedy;
			break;	
			
		case 'G':
			if (!parser.isItThere(PRDir)) {
				throw std::runtime_error("ERROR: Please specify a Path-Relinking Direction as well!");
			}
			param.PRMeth = PRMethGRASP;
			break;
		
		case 'n':
			if (!parser.isItThere(PRDir)) {
				throw std::runtime_error("ERROR: Please specify a Path-Relinking Direction as well!");
			}
			param.PRMeth = PRMethNone;
			break;
			
		default:
			throw std::runtime_error("ERROR: Please specify the Path-Relinking Selection Methods.");	
	}
	
	switch (PRDir.value()) {
		case 'f':
			param.PRDir = PRDirForward;
			break;
			
		case 'b':
			param.PRDir = PRDirBackward;
			break;
			
		case 'm':
			param.PRDir = PRDirMixed;
			break;
		
		default:
			throw std::runtime_error("ERROR: Please specify the Path-Relinking Direction.");	
	}
	
	switch (PRPoolSelect.value()) {
		case 'r':
			param.PRPoolSelect = PRPoolSelectRandom;
			break;
		
		case 'd':
			param.PRPoolSelect = PRPoolSelectDiverse;
			break;
		
		case 'a':
			param.PRPoolSelect = PRPoolSelectAll;
			break;
		
		default:
			throw std::runtime_error("ERROR: Specify a Pool Selection Criterion.");
	}
	
	if (param.PRMeth != PRMethNone) {
		if (param.PRPoolSize <= 0) {
			throw std::runtime_error("ERROR: Please make sure to use Pool Size greater than 0");
		}
	}
} 

#endif	