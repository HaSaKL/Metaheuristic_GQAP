#include "GQAP.h"

/* C O N S T R U C T O R S    +     D E S T R U C T O R S*/
// Default Constructor
GQAP::GQAP() {
	solution = eoVector<eoMinimizingFitness, int>(0,0);
	
	transportCost = 1;
	
	numLocation = 0;
	numEquip 	= 0;
	
	vectorSpaceCap = std::vector<int>();
	vectorSpaceReq = std::vector<int>();
	
	matrixDist 			= std::vector<std::vector<double> >();
	matrixFlow 			= std::vector<std::vector<double> >();
	matrixInstallCost 	= std::vector<std::vector<double> >();
	
	numViolatedLocations 	= 0;
	numViolatedCapacityUnits = 0;
	
	UsedCapacity = std::vector<int>();
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
	for (int i = 0; i < numEquip; i++) {
			for (int j = 0; j < numEquip; j++) {
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
	for (int k = 0; k < numLocation; k++) {
		for (int h = 0; h < numLocation; h++) {
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
	for (int i = 0; i < numEquip; i++) {
		for (int k = 0; k < numLocation; k++) {
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
	for (int i = 0; i < numEquip; i++) {
		file >> vectorSpaceReq[i];
	}
	
	// Read Space Capacity of Locations
	vectorSpaceCap.resize(numLocation);
	for (int k = 0; k < numLocation; k++) {
		file >> vectorSpaceCap[k];
	}
	
	// close problem file stream
	file.close();
	
	// Initialize Solution Vector
	solution.resize(numEquip);
	
	installationPenalty   = maxInstallCost;
	transportationPenalty = maxDist * maxFlow;
	
	UsedCapacity = std::vector<int>(numLocation, 0);
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

void GQAP::operator=(GQAP_Solution& _solution) {
	if (_solution.solution.size() != solution.size()) {
		throw std::runtime_error("ERROR: Trying to GQAP_Solution with differen size to a GQAP");
	}
	
	for (int i = 0; i < solution.size(); i++) {
		solution[i] = _solution[i];
	}
	
	fitness(_solution.fitness());
	CalculateCapacityViolations();
}

// Conversion Operator
GQAP::operator GQAP_Solution() {
	GQAP_Solution tmp;
	
	tmp.solution.resize(solution.size());
	
	for (int i = 0; i <= solution.size(); i++) {
		tmp.solution[i] = solution[i];
	}
		
	tmp.fitness(fitness());
	
	return tmp;
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

const std::vector<int>& GQAP::GetUsedCapacity() const {
	return UsedCapacity;
}
int GQAP::GetUsedCapacity(int location) const {
	return UsedCapacity[location];
}

double GQAP::GetInstallationPenalty() const {
	return installationPenalty;
}

double GQAP::GetTransportationPenalty() const {
	return transportationPenalty;
}

int GQAP::GetNumViolatedLocations() const {
	return numViolatedLocations;
}

double GQAP::GetNumViolatedCapacityUnits() const {
	return numViolatedCapacityUnits;
}


/* P R O B L E M   -   S P E C I F I C    F U N C T I O N S */

void GQAP::fullEvaluation() {
	// Full Problem Evaluation, Calcualtes Objective Value for Current Solution
	double totalCosts = 0;
	double totalCostsWithOutPenalty = 0;
	double totalInstallationCosts = 0;
	double totalTransportationCosts = 0;
	double totalPenaltyCosts = 0;
	
	// Calculate Installation Costs
	for (int i = 0; i < numEquip; i++) {
		totalInstallationCosts = totalInstallationCosts + matrixInstallCost[i][solution[i]];
	}
	
	// Calculate Transportation Costs
	for (int i = 0; i < numEquip; i++) {
		for (int j = i; j < numEquip; j++) {
			totalTransportationCosts = totalTransportationCosts 
										+ matrixFlow[i][j] * matrixDist[solution[i]][solution[j]] 
										+ matrixFlow[j][i] * matrixDist[solution[j]][solution[i]];
		}
	}
	
	// Calcualte Total Costs w/o Penalty
	totalCostsWithOutPenalty = totalInstallationCosts + transportCost * totalTransportationCosts;
	
	
	// Calculate Penalty Costs
	CalculateCapacityViolations();
	totalPenaltyCosts = numViolatedLocations * installationPenalty 
						+ transportCost * numViolatedCapacityUnits * transportationPenalty;
	
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


void GQAP::CalculateCapacityViolations() {
	// Calculates the number of Locations with violated capacity restrictions for Current Solution
	// and the extend of the total violation over all locations for the current solution
	
	numViolatedLocations = 0;
	numViolatedCapacityUnits = 0;
	
	// Calculate Capacity Requirements of each Location for Current Solution
	UsedCapacity = std::vector<int>(numLocation, 0);
	for (int i = 0; i < numEquip; i++) {
		UsedCapacity[solution[i]] += vectorSpaceReq[i];
	}
	
	// Calculate Violation
	int CapDelta = 0;
	div_t divresult;
	for (int k = 0; k < numLocation; k++) {
		CapDelta = UsedCapacity[k] - vectorSpaceCap[k];
		if (CapDelta > 0 ) {
			// if condition is important not only for adding the right amount to numViolatedCapacityUnits
			// but aĺso for making sure the right number of violated locations is added
			// problematic would be CapDelta = 0 -> in this case there would still be one violated location
			
			// substract one from UsedCapacity to make sure that only one location is added to
			// numViolatedLocations if e.g. UsedCap = 40 and avaiable Space is 20 --> this could 
			// fit in the original and one additional location, but intger diff would result in
			// two additional locations
			divresult = div(UsedCapacity[k]-1, vectorSpaceCap[k]);
			
			numViolatedLocations = numViolatedLocations + divresult.quot;
			numViolatedCapacityUnits = numViolatedCapacityUnits + CapDelta;
		}
	}
	
	/* // DEBUG
	std::cout << "Called CalculateCapacityViolation() " << std::endl;
	std::cout << "numViolatedLocations:     " << numViolatedLocations << std::endl;
	std::cout << "numViolatedCapacityUnits: " << numViolatedCapacityUnits << std::endl;
	for(int k = 0; k < numLocation; k++) {
		std::cout << "Cap used @ location " << k << ": " << UsedCapacity[k] << std::endl;
	}
	// */
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
	numViolatedCapacityUnits  = _problem.numViolatedCapacityUnits;
	numViolatedLocations     = _problem.numViolatedLocations;
	
	installationPenalty	  = _problem.installationPenalty;
	transportationPenalty = _problem.transportationPenalty;
	
	UsedCapacity = _problem.UsedCapacity;
}




/* I N I T I A L I Z A T I O N S */

void GQAP::RandomInit() {
	// Random Problem Initialization
	for (int i = 0; i < numEquip; i++) {
		solution[i] = rng.random(numLocation);
	}
}


void GQAP::GRASPInit(double alpha) {
	// GRASP-Initialization using the provided alpa-value
	
	// if Random-Initialization is choosen, then do random initialization, since it is much faster
	// GRASP-Init with alpha = 0 is equal to random initialization
	if (alpha == 1) {
		RandomInit();
		
	// do GRASP-Init, if alpha > 0
	} else {
		// Define a Vector holing the Restricted Candidate List with maximum size
		std::vector<RCL_element> candidateList(numLocation*numEquip);
	
		// current Assignment
		Assignment cAssign;
	
		// set the current solution to an undefined representation to distinguish it from valid partial solution
		//solution = std::vector<int>(numEquip, -1);
		solution = eoVector<eoMinimizingFitness, int>(numEquip, -1);
	
		// reset the values for capacity violations
		numViolatedLocations = 0;
		numViolatedCapacityUnits = 0;
	
		// Initialize the RCL
		GRASPInitCandidateList(candidateList);
	
		// Add Assignments, until solution has been constructed
		while (candidateList.size() > 0) {
			GRASPAddAssignment_CostBased(candidateList, alpha);
			GRASPUpdateCandidateList(candidateList);
		}
	}
	
}


void GQAP::GRASPInitCandidateList(std::vector<RCL_element>& _rcl) {
	// Initialize the Candidate List
	
	// the list only considers installation costs,
	// since to previous assignment is known and therefore no transportation is needed
	double costs;
	int idx = 0;
	Assignment cAssign;
	
	// loop through all Equipment - Location Combinations
	// and add them to the RCL with their respective installation costs
	for (int i = 0; i < numEquip; i++) {
		for (int k = 0; k < numLocation; k++) {
			cAssign.first = i;
			cAssign.second = k;
			costs = matrixInstallCost[i][k];
			_rcl[idx] = RCL_element(costs, cAssign);
			idx++;
		}
	}
	
	/*// DEBUG: Print RCL
	for (int i=0; i < _rcl.size(); i++) {
		std::cout << _rcl[i].second.first << " -> " << _rcl[i].second.second << ": " << _rcl[i].first << std::endl;
	}
	std::cout << std::endl<<std::endl;
	//*/
}


void GQAP::GRASPAddAssignment_CostBased(std::vector<RCL_element>& _rcl, double alpha) {
	// randomly chooses an additional assignment to add to the solution and 
	// removes other possible assignments for same equipment from the RCL
	
	// order the RCL by its costs values
	std::sort(_rcl.begin(), _rcl.end());
	
	// select a member of the RCL randomly using the alpha-parameter
	// while considering the cut-off cost for the RCL (value-based RCL)
	double minCostIncrease = _rcl.front().first;
	double maxCostIncrease = _rcl.back().first;
	double maxRCLCost = minCostIncrease + alpha * (maxCostIncrease - minCostIncrease);
	
	// find first index of sorted RCL list element with higher then cut-off costs
	// implementaion using std::upper_bound does not work b/c of type is 
	// RCL_element and not astandard data type
	int i = 0;
	while (i < _rcl.size()) {
		if(_rcl[i].first >= maxRCLCost) {
			break;
		} else {
			i++;
		}
	}
	
	// choose an assignment from the resticted list randomly
	int idxRCL = rng.random(i+1); 	// draw from [0,i+1)
	int cEquipment = _rcl[idxRCL].second.first;
	int cLocation  = _rcl[idxRCL].second.second;
	
	// add choosen assignment to solution
	solution[cEquipment] = cLocation;
	
	// remove the selected Equipment from the RCL;
	i = 0;
	while (i < _rcl.size()) {
		if (_rcl[i].second.first == cEquipment) {
			_rcl.erase(_rcl.begin() + i);
		} else {
			i++;
		}
	}
	
	// update the capacity utilization after the new assignment
	GRASPUpdateCapacityViolation(cEquipment, cLocation);
	
	/* // DEBUG Print choosen Assignment
	std::cout << "MaxRCL Costs (cut-off if >= :" << maxRCLCost << std::endl;
	std::cout << "Choosen Assignment: " << cEquipment << " -> " << cLocation << std::endl;
	// */
}


void GQAP::GRASPUpdateCapacityViolation(int Equipment, int Location) {
	
	// Update the effect of an added assignment on the violation of the constraints
	int tempViolatedLocations = numViolatedLocations;
	int tempViolatedCapacityUnits = numViolatedCapacityUnits;
	std::vector<int> tempUsedCapacity = UsedCapacity;
	
	GRASPCalculateCapacityViolation(Equipment, Location, tempViolatedLocations, tempViolatedCapacityUnits, tempUsedCapacity);
	
	numViolatedLocations = tempViolatedLocations;
	numViolatedCapacityUnits = tempViolatedCapacityUnits;
	UsedCapacity = tempUsedCapacity;
}


void GQAP::GRASPCalculateCapacityViolation(int Equipment, int Location, int & _numViolatedLocations, int & _numViolatedCapcityUnits, std::vector<int> & _UsedCapacity) {
	// Calculate the effect of an added assignment on the violations of the constraints
	
	// Calculate old numViolatedCapcityUnits of Location
	div_t divresult_old;
	divresult_old = div(_UsedCapacity[Location], vectorSpaceCap[Location]);
	
	
	// Calculate new Capacity Requirement for Location of new Assignment
	_UsedCapacity[Location] += vectorSpaceReq[Equipment];
	
	
	// See if Capacity is violated, if so: update variables for penalty cost calculations
	int CapDelta = _UsedCapacity[Location] - vectorSpaceCap[Location];
	if (CapDelta > 0) {
		div_t divresult_new;
		divresult_new = div(_UsedCapacity[Location], vectorSpaceCap[Location]);
		_numViolatedLocations =+  divresult_new.quot - divresult_old.quot;
		_numViolatedCapcityUnits =+ CapDelta;
	}
	
}


void GQAP::GRASPUpdateCandidateList(std::vector<RCL_element>& _rcl) {
	// now update the RCL of all possible assignments and calculate their 
	// cost increase. In the latter aspect, this differs from the 
	// initialization, where only installation cost was relevant
	
	double costs;
	Assignment cAssign;
	for (int i = 0; i < _rcl.size(); i++) {
		cAssign.first  = _rcl[i].second.first;
		cAssign.second = _rcl[i].second.second;
		costs = GRASPCalculateCostIncrease(cAssign);
		_rcl[i] = RCL_element(costs, cAssign);
	}
	
	/*// DEBUG Print Candidate List
	std::cout << "New Candidate List " << std::endl;
	for (int i=0; i < _rcl.size(); i++) {
		std::cout << _rcl[i].second.first << " -> " << _rcl[i].second.second << ": " << _rcl[i].first << std::endl;
	}
	std::cout << std::endl<<std::endl;
	//*/
}


double GQAP::GRASPCalculateCostIncrease(Assignment& _assign) {
	// Calculates the increase in total costs for the given Assignment
	double totalIncrease = 0.0;
	double totalInstallationCostsIncrease   = 0.0;
	double totalTransportationCostsIncrease = 0.0;
	double totalPenaltyCostsIncrease = 0.0;
	
	int Equipment = _assign.first;
	int Location  = _assign.second;
	
	// Calculate Increase in Installation Costs	
	totalInstallationCostsIncrease = matrixInstallCost[Equipment][Location];
	
	
	
	// Calculate Increase in Transportation Costs
	for (int i = 0; i < numEquip; i++) {
		// consider only transportation to equipment which has already been assigned!
		// thus, solution[i] != -1 --> solution[i]>= 0
		if(solution[i] >= 0) { 
			totalTransportationCostsIncrease = totalTransportationCostsIncrease
												+ matrixFlow[i][Equipment] * matrixDist[solution[i]][Location]
												+ matrixFlow[Equipment][i] * matrixDist[Location][solution[i]];
		}
	}
	
	// Calculate Increase in Penalty Costs	
	int newNumViolatedLocations = numViolatedLocations;
	int newNumViolatedCapcityUnits = numViolatedCapacityUnits;
	std::vector<int> tmpUsedCapacity = UsedCapacity;
	
	GRASPCalculateCapacityViolation(Equipment, Location, newNumViolatedLocations, newNumViolatedCapcityUnits, tmpUsedCapacity);
	
	int deltaNumViolatedLocations    = newNumViolatedLocations    - numViolatedLocations;
	int deltaNumViolatedCapcityUnits = newNumViolatedCapcityUnits - numViolatedCapacityUnits;
	
	totalPenaltyCostsIncrease = installationPenalty * deltaNumViolatedLocations
							  +  transportationPenalty * deltaNumViolatedCapcityUnits * transportCost;

	totalIncrease = totalInstallationCostsIncrease + totalPenaltyCostsIncrease + totalTransportationCostsIncrease;
	
	return totalIncrease;
}

GQAP_Solution GQAP::GetSolution() {
	GQAP_Solution tmp;
	
	tmp.solution.resize(GetNumEquip());
	
	for (int i = 0; i < solution.size(); i++) {
		tmp.solution[i] = solution[i];
	}
		
	tmp.fitness(fitness());
	
	return tmp;
}
