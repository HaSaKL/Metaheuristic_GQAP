#include "GQAP.h"

/* C O N S T R U C T O R S    +     D E S T R U C T O R S*/
// Default Constructor
GQAP::GQAP() {
	solution = std::vector<int>();
	
	transportCost = 1;
	
	numLocation = 0;
	numEquip 	= 0;
	
	vectorSpaceCap = std::vector<int>();
	vectorSpaceReq = std::vector<int>();
	
	matrixDist 			= std::vector<std::vector<double> >();
	matrixFlow 			= std::vector<std::vector<double> >();
	matrixInstallCost 	= std::vector<std::vector<double> >();
	
	numViolatedLocations 	= 0;
	numViolatedCapcityUnits = 0;
}


// Copy Constructor
GQAP::GQAP(GQAP & _problem) {
	CopyProblem(_problem);
}


// Construct from Problem File
GQAP::GQAP(std::string& _fileName) {
	
	// initialize varaibles to find out maximum parameter values in parameter matrices
	std::vector<double>::const_iterator it;
	double maxDist = 0;
	double maxFlow = 0;
	double maxInstallCost = 0;
	
	
	// open new file stream to read problem
	std::fstream file(_fileName.c_str(), std::ios::in);
	
	// check if file is actually open now
	// FIXME: This could be more elaborated
	if(!file) {
		std::string str = "GQAP-Error: Could not open file [" + _fileName + "]";
		throw std::runtime_error(str);
	}
	
	// Read Problem Dimensions
	file >> numEquip;
	file >> numLocation;
	file >> transportCost;
	
	
	// Create and Fill Parameter Matrices according to Problem Dimensions
	// definte temporary row vector to read data from matrices row-wise
	std::vector<double> vecTemp;
	
	// Read Flow between Equipments
	vecTemp.resize(numEquip);
	matrixFlow.resize(numEquip);
	for (unsigned int i = 0; i < numEquip; i++) {
			for (unsigned int j = 0; j < numEquip; j++) {
				file >> vecTemp[j];
			}
			matrixFlow[i] = vecTemp;
			it = max_element(matrixFlow[i].begin(), matrixFlow[i].end());
			if (*it > maxFlow) {
				maxFlow = *it;
			}
	}
	
	// Read Distance between Locations
	vecTemp.resize(numLocation);
	matrixDist.resize(numLocation);
	for (unsigned int k = 0; k < numLocation; k++) {
		for (unsigned int h = 0; h < numLocation; h++) {
			file >> vecTemp[h];
		}
		matrixDist[k] = vecTemp;
		it = max_element(matrixDist[k].begin(), matrixDist[k].end());
		if (*it > maxDist) {
			maxDist = *it;
		}
	}
	
	// Read Installation Costs
	vecTemp.resize(numLocation);
	matrixInstallCost.resize(numEquip);
	for (unsigned int i = 0; i < numEquip; i++) {
		for (unsigned int k = 0; k < numLocation; k++) {
			file >> vecTemp[k];
		}
		matrixInstallCost[i] = vecTemp;
		it = max_element(matrixInstallCost[i].begin(), matrixInstallCost[i].end());
		if (*it > maxInstallCost) {
			maxInstallCost = *it;
		}
	}
	
	// Read Space Requirements of Equipment
	vectorSpaceReq.resize(numEquip);
	for (unsigned int i = 0; i < numEquip; i++) {
		file >> vectorSpaceReq[i];
	}
	
	// Read Space Capacity of Locations
	vectorSpaceCap.resize(numLocation);
	for (unsigned int k = 0; k < numLocation; k++) {
		file >> vectorSpaceCap[k];
	}
	
	// close problem file stream
	file.close();
	
	// Initialize Solution Vector
	solution.resize(numEquip);
	
	installationPenalty   = maxInstallCost;
	transportationPenalty = maxDist * maxFlow;
}


// Destructor
GQAP::~GQAP() {
	// no additional operations nessessary, since only standard vectors are used
}


/* O V E R L O A D E D     O P E R A T O R S*/
// Subsetting Operator
int& GQAP::operator [](int equipment) {
	return solution[equipment];
}

// Assignment Operator
void GQAP::operator =(GQAP & _problem) {
	CopyProblem(_problem);
}


/* G E T T E R  -  F U N C T I O N S*/

int GQAP::GetTransportCost() const {
	return transportCost;
}

int GQAP::GetNumLocation() const {
	return numLocation;
}

int GQAP::GetNumEquip() const {
	return numEquip;
}


const std::vector<int>& GQAP::GetVectorSpaceCap() const {
	return vectorSpaceCap;
}

int GQAP::GetVectorSpaceCap(int location) const {
	return vectorSpaceCap[location];
}

const std::vector<int>& GQAP::GetVectorSpaceReq() const {
	return vectorSpaceReq;
}

int GQAP::GetVectorSpaceReq(int equipment) const {
	return vectorSpaceReq[equipment];
}


const std::vector<std::vector<double> >& GQAP::GetMatrixDist() const {
	return matrixDist;
}
double GQAP::GetMatrixDist(int location_from, int location_to) const {
	return matrixDist[location_from][location_to];
}

const std::vector<std::vector<double> >& GQAP::GetMatrixFlow() const {
	return matrixFlow;
}
double GQAP::GetMatrixFlow(int equipment_from, int equipment_to) const {
	return matrixFlow[equipment_from][equipment_to];
}

const std::vector<std::vector<double> >& GQAP::GetMatrixInstallCost() const {
	return matrixInstallCost;
}
double GQAP::GetMatrixInstallCost(int equipment, int location) const {
	return matrixInstallCost[equipment][location];
}



// C O N V I N I E N C E   F U N C T I O N S
void GQAP::printFitness() {
	if (!invalid()) {
		std::cout << "Fitness: " << fitness() << std::endl;
	} else {
		std::cout << "Fitness is invalid. Did you Evaluate the Fitness?" << std::endl;
	}
}

void GQAP::printSolution() {
	std::cout << "Solution: ";
	for (int i = 0; i < numEquip -1; i++) {
		std::cout << solution[i] << " ; ";
	}
	std::cout << solution[numEquip-1] << std::endl;
}


/* P R O B L E M   -   S P E C I F I C    F U N C T I O N S */

void GQAP::fullEvaluation() {
	// Full Problem Evaluation, Calcualtes Objective Value for Current Solution
	// FIXME: Add Penalty Costs for exceeding Space Capacity at Locations
	double totalCosts = 0;
	double totalCostsWithOutPenalty = 0;
	double totalInstallationCosts = 0;
	double totalTransportationCosts = 0;
	double totalPenaltyCosts = 0;
	
	// Calculate Installation Costs
	for (unsigned int i = 0; i < numEquip; i++) {
		totalInstallationCosts = totalInstallationCosts + matrixInstallCost[i][solution[i]];
	}
	
	// Calculate Transportation Costs
	for (unsigned int i = 0; i < numEquip; i++) {
		for (unsigned int j = i; j < numEquip; j++) {
			totalTransportationCosts = totalTransportationCosts 
										+ matrixFlow[i][j] * matrixDist[solution[i]][solution[j]] 
										+ matrixFlow[j][i] * matrixDist[solution[j]][solution[i]];
		}
	}
	
	// Calcualte Total Costs w/o Penalty
	totalCostsWithOutPenalty = totalInstallationCosts + transportCost * totalTransportationCosts;
	
	
	// Calculate Penalty Costs
	CalculateCapacityViolations();
	totalPenaltyCosts = numViolatedLocations * installationPenalty + transportCost * numViolatedCapcityUnits * transportationPenalty;
	
	// Calculate Total Costs
	totalCosts = totalCostsWithOutPenalty + totalPenaltyCosts;
	
	/*// DEBUG
	std::cout << "fullEval Partial Costs:" << std::endl;
	std::cout << "total Installation Costs:   " << totalInstallationCosts << std::endl;
	std::cout << "total Transportation Costs: " << totalTransportationCosts << std::endl;
	std::cout << "total Cost without Penalty: " << totalCostsWithOutPenalty << std::endl;
	std::cout << "total Penalty Costs:        " << totalPenaltyCosts << std::endl;
	std::cout << "total Costs:                " << totalCosts << std::endl;
	//*/
	
	// Update Fitness
	fitness(totalCosts);
}


void GQAP::RandomInit() {
	// Random Problem Initialization
	for (unsigned int i = 0; i < numEquip; i++) {
		solution[i] = rng.random(numLocation);
	}
}

void GQAP::GRASPInit(double alpha) {
	std::string str = "GQAP-Error: GRASP-Init not yet implemented!";
	throw std::runtime_error(str);
}



void GQAP::CopyProblem(GQAP & _problem) {
	// Copy Problem Parameters
	transportCost 	= _problem.transportCost;
	numLocation 	= _problem.numLocation;
	numEquip 		= _problem.numEquip;
	vectorSpaceCap 	= _problem.vectorSpaceCap;
	vectorSpaceReq 	= _problem.vectorSpaceReq;
	matrixDist 		= _problem.matrixDist;
	matrixFlow 		= _problem.matrixFlow;
	matrixInstallCost = _problem.matrixInstallCost;
	
	// Copy Current Solution and its Fitness-Value
	solution = _problem.solution;
	if (!_problem.invalid()) {
		fitness(_problem.fitness());
	}
	
	// Copy Helper Variables
	numViolatedCapcityUnits  = _problem.numViolatedCapcityUnits;
	numViolatedLocations     = _problem.numViolatedLocations;
}

void GQAP::CalculateCapacityViolations() {
	// Calculates the number of Locations with violated capacity restrictions for Current Solution
	// and the extend of the total violation over all locations for the current solution
	
	numViolatedLocations = 0;
	numViolatedCapcityUnits = 0;
	
	// Calculate Capacity Requirements of each Location for Current Solution
	std::vector<unsigned int> UsedCapacity(numLocation, 0);
	for (unsigned int i = 0; i < numEquip; i++) {
		UsedCapacity[solution[i]] += vectorSpaceReq[i];
	}
	
	// Calculate Violation
	int CapDelta = 0;
	div_t divresult;
	for (unsigned int k = 0; k < numLocation; k++) {
		CapDelta = UsedCapacity[k] - vectorSpaceCap[k];
		if (CapDelta > 0 ) {
			divresult = div(UsedCapacity[k], vectorSpaceCap[k]);
			numViolatedLocations =+ divresult.quot + 1;
			numViolatedCapcityUnits =+ CapDelta;
		}
	}
}
