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
	
	// Calculate Cost Increase
	double incrTotal = 0;
	incrTotal = CalculateIncrCosts(equipment, newLocation, oldLocation);
	
	/*// DEBUG OUTPUT
	std::cout << "Move Equipment " << equipment << " from location " << oldLocation << " to " << newLocation << std::endl;
	std::cout << "Old Solution Value: " << _solution.fitness() << std::endl;
	std::cout << "Increase:           " << incrTotal << std::endl;
	std::cout << "New Solution Value: " << _solution.fitness() + incrTotal << std::endl << std::endl;
	// */
	
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
								(_problem -> GetMatrixDist(_problem->solution[i],newLocation)	// add flow to new location
								 -_problem -> GetMatrixDist(_problem->solution[i],oldLocation)	// substract flow to old location
								 )
							+ _problem -> GetMatrixFlow(equipment,i) * 
								(_problem -> GetMatrixDist(newLocation,_problem->solution[i])  // add flow from new location
								- _problem -> GetMatrixDist(oldLocation,_problem->solution[i]) // substract flow from old location
								 );
		}
	}
	
	// Calculate the Change in Penalty Costs	
	// first calucate the amount of capacity violations for old and new assignment @ old and new location
	int deltaCap;
	
	deltaCap = _problem->GetVectorSpaceCap(oldLocation) - _problem->GetUsedCapacity(oldLocation);
	int CapViolationOldLocOldSol = deltaCap * (deltaCap < 0) * -1;
	
	deltaCap = _problem->GetVectorSpaceCap(oldLocation) - _problem->GetUsedCapacity(oldLocation) + _problem->GetVectorSpaceReq(equipment);
	int CapViolationOldLocNewSol = deltaCap * (deltaCap < 0) * -1;
	
	deltaCap = _problem->GetVectorSpaceCap(newLocation) - _problem->GetUsedCapacity(newLocation);
	int CapViolationNewLocOldSol = deltaCap * (deltaCap < 0) * -1;
	
	deltaCap = _problem->GetVectorSpaceCap(newLocation) - _problem->GetUsedCapacity(newLocation) - _problem->GetVectorSpaceReq(equipment);
	int CapViolationNewLocNewSol = deltaCap * (deltaCap < 0) * -1;
	
	// calculate the number of violated capacity units
	int deltaNumViolatedCapacityUnits = 
						CapViolationNewLocNewSol - CapViolationNewLocOldSol 
						+ (CapViolationOldLocNewSol - CapViolationOldLocOldSol);
	
	// calculate the change in the number of violated locations using INTEGER devision on POSIVIE numbers only
	// substract one from Used Capacity b/c otherwiese more locations will be flagged as violated
	// e.g.: Location Capacity = 20, Used Capacity = 20 --> 20/20 = 1 but there is no violation
	// same holds true for 40/20 = 2 but there should be only one violation, since there is enough space
	// in the original + the additional location installation
	// this seems like a quick and dirty fix, but sinde capacity is inter-valued this works well
	int LocViolationOldLocOldSol = (_problem->GetUsedCapacity(oldLocation)-1)/ _problem->GetVectorSpaceCap(oldLocation);
	int LocViolationOldLocNewSol = (_problem->GetUsedCapacity(oldLocation)-1 - _problem->GetVectorSpaceReq(equipment)) / _problem->GetVectorSpaceCap(oldLocation);
	int LocViolationNewLocOldSol = (_problem->GetUsedCapacity(newLocation)-1)/ _problem->GetVectorSpaceCap(newLocation);
	int LocViolationNewLocNewSol = (_problem->GetUsedCapacity(newLocation)-1 + _problem->GetVectorSpaceReq(equipment)) / _problem->GetVectorSpaceCap(newLocation);
	int deltaNumViolatedLocations = 
						LocViolationNewLocNewSol - LocViolationNewLocOldSol
						+ (LocViolationOldLocNewSol - LocViolationOldLocOldSol);
	
	
	
	double IncrPenalty = deltaNumViolatedLocations * _problem->GetInstallationPenalty()
				 + deltaNumViolatedCapacityUnits * _problem->GetTransportationPenalty() * _problem->GetTransportCost();
	
	double TotalIncr = IncrInstall + IncrTransport * _problem->GetTransportCost() + IncrPenalty;
	
	/*// DEBUG OUTPUT
	std::cout << "CapViolation Old Loc New Sol:       " << CapViolationOldLocNewSol << std::endl;
	std::cout << "CapViolation Old Loc Old Sol:       " << CapViolationOldLocOldSol << std::endl;
	std::cout << "CapViolation New Loc New Sol:       " << CapViolationNewLocNewSol << std::endl;
	std::cout << "CapViolation New Loc Old Sol:       " << CapViolationNewLocOldSol << std::endl;
	std::cout << std::endl;
	std::cout << "LocViolation Old Loc New Sol:       " << LocViolationOldLocNewSol << std::endl;
	std::cout << "LocViolation Old Loc Old Sol:       " << LocViolationOldLocOldSol << std::endl;
	std::cout << "LocViolation New Loc New Sol:       " << LocViolationNewLocNewSol << std::endl;
	std::cout << "LocViolation New Loc Old Sol:       " << LocViolationNewLocOldSol << std::endl;
	std::cout << std::endl;
	std::cout << "Delta Number of Violated Locations: " << deltaNumViolatedLocations << std::endl;
	std::cout << "Delta Number of Violated Cap Units: " << deltaNumViolatedCapacityUnits << std::endl;
	std::cout << std::endl;
	std::cout << "Transporation Penalty:              " << _problem->GetTransportationPenalty() << std::endl;;
	std::cout << "Installation Penalty:               " << _problem->GetInstallationPenalty() << std::endl;;
	std::cout << "Transportation Costs:               " << _problem->GetTransportCost() << std::endl;;
	std::cout << std::endl;
	std::cout << "Penalty for Location Violation:     " << deltaNumViolatedLocations * _problem->GetInstallationPenalty() << std::endl;
	std::cout << "Penalty for Cap. Unit Violations:   " << deltaNumViolatedCapacityUnits * _problem->GetTransportationPenalty() * _problem->GetTransportCost() << std::endl;
	std::cout << "Resulting Incr in Penalty Costs:    " << IncrPenalty << std::endl;;
	std::cout << "Incr in Installation Costs:         " << IncrInstall << std::endl;;
	std::cout << "Incr in Transport Flow:             " << IncrTransport << std::endl;;
	//*/
	
	return TotalIncr;
}
