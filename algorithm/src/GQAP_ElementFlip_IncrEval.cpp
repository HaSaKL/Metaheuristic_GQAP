#include "GQAP_ElementFlip_IncrEval.h"

// Constructor
GQAP_ElementFlip_IncrEval::GQAP_ElementFlip_IncrEval(GQAP & _probObj) {
	_problem = & _probObj;
}
	
// Interface function
void GQAP_ElementFlip_IncrEval::operator() (GQAP_ElementFlipIndex_Neighbor::EOT & _solution, GQAP_ElementFlipIndex_Neighbor & _neighbor) {
	// Calculate Increased Costs and Update Fitness Value
	
	// get indices of changes assignment
	int equipment;
	int newLocation;
	int oldLocation;
	
	_neighbor.getMove(equipment, newLocation, _solution);
	oldLocation = _problem -> solution[equipment];
	
	// DEBUG OUTPUT
	std::cout << "Move Equipment " << equipment << " from location " << oldLocation << " to " << newLocation << std::endl;
	/*std::cout << "Old Solution Value: " << _solution.fitness() << std::endl;
	std::cout << "Increase:           " << incrTotal << std::endl;
	std::cout << "New Solution Value: " << _solution.fitness() + incrTotal << std::endl << std::endl;
	// */
	
	// Calculate Cost Increase
	double incrTotal = CalculateIncrCosts(equipment, newLocation, oldLocation);
	
	// Set new Costs
	_neighbor.fitness(_solution.fitness() + incrTotal);
}

// actual Calculation
double GQAP_ElementFlip_IncrEval::CalculateIncrCosts (int equipment, int newLocation, int oldLocation) {
	// Calculate the Costs Increase/Decrease for the changes assignment
	
	// Calculate the Change in Installation Costs
	double IncrInstall = _problem->GetMatrixInstallCost(equipment, newLocation) 
						- _problem->GetMatrixInstallCost(equipment, oldLocation);
					
	// Calculate the Change in Transportation Costs
	double IncrTransport = 0;
	int numEquipment = _problem->GetNumEquip();
	for (int i = 0; i < numEquipment; i++) {
		// only consider Transportation to all OTHER Equipment
		if (i != equipment) {
			IncrTransport = IncrTransport
							+ _problem -> GetMatrixFlow(i,equipment) * 
								(_problem -> GetMatrixDist(_problem -> solution[i],newLocation)		// add flow to new location
								 -_problem -> GetMatrixDist(_problem -> solution[i],oldLocation)	// substract flow to old location
								 )
							+ _problem -> GetMatrixFlow(equipment,i) * 
								(_problem -> GetMatrixDist(newLocation,_problem -> solution[i]) 	// add flow from new location
								- _problem -> GetMatrixDist(oldLocation,_problem -> solution[i]) // substract flow from old location
								 );
		}
	}
	
	// Calculate the Change in Penalty Costs	
	// first calucate the amount of capacitty violations for old and new assignment @ old and new location
	int dummy;
	dummy = _problem->GetVectorSpaceCap(oldLocation) - _problem->GetUsedCapacity(oldLocation);
	std::cout << "SpaceCap(" << _problem->GetVectorSpaceCap(oldLocation) << ") - SpaceUsed(" << _problem->GetUsedCapacity(oldLocation) << ") = CapViolation(" << dummy * (dummy < 0) * -1 << ")" << std::endl;
	int CapViolationOldLocOldSol = dummy * (dummy < 0) * -1;
	
	dummy = _problem->GetVectorSpaceCap(oldLocation) - _problem->GetUsedCapacity(oldLocation) + _problem->GetVectorSpaceReq(equipment);
	int CapViolationOldLocNewSol = dummy * (dummy < 0) * -1;
	
	dummy = _problem->GetVectorSpaceCap(newLocation) - _problem->GetUsedCapacity(newLocation);
	int CapViolationNewLocOldSol = dummy * (dummy < 0) * -1;
	
	dummy = _problem->GetVectorSpaceCap(newLocation) - _problem->GetUsedCapacity(newLocation) - _problem->GetVectorSpaceReq(equipment);
	int CapViolationNewLocNewSol = dummy * (dummy < 0) * -1;
	
	
	// calculate the change in the number of violated locations and of violated capacity units
	int deltaNumViolatedLocations = 
						(CapViolationNewLocNewSol > 0) - (CapViolationNewLocOldSol > 0)
						- (CapViolationOldLocOldSol > 0) + (CapViolationOldLocNewSol > 0);
	
	int deltaNumViolatedCapacityUnits = 
						CapViolationNewLocNewSol - CapViolationNewLocOldSol 
						- CapViolationOldLocOldSol + CapViolationOldLocNewSol;
	
	double IncrPenalty = deltaNumViolatedLocations * _problem->GetInstallationPenalty()
				 + deltaNumViolatedCapacityUnits * _problem->GetTransportationPenalty() * _problem->GetTransportCost();
	
	double TotalIncr = IncrInstall + IncrTransport * _problem->GetTransportCost() + IncrPenalty;
	
	// DEBUG OUTPUT
	std::cout << "CapViolation Old Loc New Sol:       " << CapViolationOldLocNewSol << std::endl;
	std::cout << "CapViolation Old Loc Old Sol:       " << CapViolationOldLocOldSol << std::endl;
	std::cout << "CapViolation New Loc New Sol:       " << CapViolationNewLocNewSol << std::endl;
	std::cout << "CapViolation New Loc Old Sol:       " << CapViolationNewLocOldSol << std::endl;
	
	std::cout << "Delta Number of Violated Locations: " << deltaNumViolatedLocations << std::endl;
	std::cout << "Delta Number of Violated Cap Units: " << deltaNumViolatedCapacityUnits << std::endl;
	
	std::cout << "Transporation Penalty:              " << _problem->GetTransportationPenalty() << std::endl;;
	std::cout << "Installation Penalty:               " << _problem->GetInstallationPenalty() << std::endl;;
	std::cout << "Transportation Costs:               " << _problem->GetTransportCost() << std::endl;;
	std::cout << "Resulting Incr in Penalty Costs:    " << IncrPenalty << std::endl;;
	std::cout << "Incr in Installation Costs:         " << IncrInstall << std::endl;;
	std::cout << "Incr in Transport Flow:             " << IncrTransport << std::endl;;
	//*/
	
	return TotalIncr;
}