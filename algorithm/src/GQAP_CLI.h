/* This source file descripes the parameters and default values
 * which make up the command line interface to the GRASP implementation
 * */
#ifndef GQAP_CLI_H
#define GQAP_CLI_H

#include <eo>


// DEFINITION OF CONSTANTS FOR DIFFERENT ALGORITHM CONFIGURATIONS

// LOCAL SEARCH PHASE
static const int LSStrategyBestImprov   = 0;	// During LS Select best Neighbor in Neighborhood
static const int LSStrategyRandomImprov = 1;	// Randomly search Neighhood and select First Improvement

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
	
	// lo
	cal search Algorithm selection
	// 'b' - Best Improvement
	// 'f' - First Random Improvement
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
	
	
	// Selection of Alpha Value for Initialization
	// 'r' - Random Initialization
	// 'g' - Greedy Initialization
	// ### - GRASP Initialization with Alpha Fixed to ###
	// 'R' - GRASP Initialization with Reactive Alpha Value
	// 'U' - GRASP with Uniformly Distributed Alpha
	// Number - fixed Alpha Value
	std::string StartSol;
	
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

	// For each parameter, you can in on single line
	// define the parameter, read it through the parser, and assign it
	param.seed = parser.createParam( 
		unsigned(time(0)),
		"seed",
		"Random number seed",
		'S'
		).value();
										
	param.problemFile = parser.createParam( 
		std::string("../../problems/Test4-10-5.dat"),
		"problemFile",
		"Path to problem file",
		'p',
		"Param"
		).value();	
	
	param.outputFile = parser.createParam(
		std::string("output.csv"),
		"resultsFile",
		"Path to the results output file",
		'o',
		"Param"
		).value();
		
	param.neighborhood = parser.createParam(
		'2',
		"neighborhood",
		"Neighborhood Type for local search",
		'n',
		"Param"
		).value();
		
	param.localSearchAlgo = parser.createParam(
		'2',
		"LSAlgo",
		"Local Search Algorithms",
		'l',
		"Param"
		).value();
		
	param.stoppingCriterion = parser.createParam(
		'?',
		"stoppingCriterion",
		"Stopping Criterion", 
		's',
		"Param"
		).value();
		
	param.alphaValue = parser.createParam(
		std::string("R"),
		"alphaValue",
		"Type of Greedy Construction Phase",
		'a',
		"Param"
		).value();
		
	param.maxRuntime = parser.createParam(
		0,
		"maxTime",
		"maximum Runtime in seconds",
		'T',
		"Param"
		).value();
		
	param.maxIterations = parser.createParam(
		0,
		"maxIter",
		"maximum number of iterations",
		'I',
		"Param"
		).value();
		
	param.targetValue = parser.createParam(
		std::numeric_limits<double>::max(), 
		"targetValue",
		"target objective value to stop at",
		't',
		"Param"
		).value();
		
		
} 

#endif	