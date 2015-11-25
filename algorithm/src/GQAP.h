#ifndef GQAP_H
#define GQAP_H

// needed for base classes and random numbers
#include <eo>
#include <vector>
#include <algorithm>
#include <cstdlib>

class GQAP : public EO<eoMinimizingFitness>
{
public:
	// actual representation of the problems solution using
	// an integer vector representing for each equipment
	// its assignment to a location
	std::vector<int> solution;

	// FIXME: Idea: Add Problem Filename so a better solution could be saved to the problem file!


	// Constructors
	GQAP();							// Default Constructor
	GQAP(GQAP& _problem);			// Copy Constructor
	GQAP(std::string& _fileName);	// From Problem File


	// Destructor
	~GQAP();


	// Operators
	void operator=(GQAP& _problem);	// Copy Assignment
	int& operator[](int equipment); // Subsetting Operator




	// Getter and Setter Methods
	int GetNumLocation() const;

	int GetNumEquip() const;

	int GetTransportCost() const;

	const std::vector<std::vector<double> >& GetMatrixDist() const;
	double GetMatrixDist(int location_from, int location_to) const;

	const std::vector<std::vector<double> >& GetMatrixFlow() const;
	double GetMatrixFlow(int equipment_from, int equipment_to) const;

	const std::vector<std::vector<double> >& GetMatrixInstallCost() const;
	double GetMatrixInstallCost(int equipment, int location) const;

	const std::vector<int>& GetVectorSpaceReq() const;
	int GetVectorSpaceReq(int equipment) const;

	const std::vector<int>& GetVectorSpaceCap() const;
	int GetVectorSpaceCap(int location) const;

	const std::vector<int>& GetUsedCapacity	() const;
	int GetUsedCapacity(int location) const;

	double GetInstallationPenalty() const;
	double GetTransportationPenalty() const;
	int GetNumViolatedLocations () const;
	double GetNumViolatedCapacityUnits() const;


	// Convinience Functions
	void printSolution();
	void printFitness();

	// Problem-specific Fuctios
	void fullEvaluation();
	void RandomInit();
	void GRASPInit(double alpha);


private:
	// Problem-Parameters
	// Number of Locations
	unsigned int numLocation;

	// Number of Equipment
	unsigned int numEquip;

	// Transportation Cost
	//FIXME: Always int? or for some instances maybe double?
	double transportCost;

	// Installation Costs for Equipment row to Location Column
	std::vector<std::vector<double> > matrixInstallCost;

	// Flow Matrix from Equipment row to Equipment column
	std::vector<std::vector<double> > matrixFlow;

	// Distance Matrix from Location row to Location column
	std::vector<std::vector<double> > matrixDist;

	// Space Requirenment of Equipment
	// FIXME: Always int? or for some instances maybe double?
	std::vector<int> vectorSpaceReq;

	// Space Capacity of Location
	std::vector<int> vectorSpaceCap;

	// Helper Variables for Penalty Calculations
	double installationPenalty;
	double transportationPenalty;
	int numViolatedLocations;
	double numViolatedCapacityUnits;
	std::vector<int> UsedCapacity;

	// Convinience Fuctions for Fitness Calculations
	void CalculateCapacityViolations();

	// Convinience Functions for Copying Parameters
	void CopyProblem(GQAP & _problem);

	// Convinience Functions for GRASP-Initialization

	// Assigenment hols the Assignment of an Equipment to a Location
	typedef std::pair<int, int> Assignment;

	// An Element of the Restricted Candidate List Adds a Cost-Function Value to an Assignment
	typedef std::pair<double, Assignment> RCL_element;


	void GRASPInitCandidateList(std::vector<RCL_element> & _rcl);
	void GRASPUpdateCandidateList(std::vector<RCL_element> & _rcl);
	void GRASPAddAssignment_CostBased(std::vector<RCL_element> & _rcl, double alpha);
	void GRASPUpdateCapacityViolation(int Equipment, int Location);
	double GRASPCalculateCostIncrease(Assignment & _assign);
	void GRASPCalculateCapacityViolation(int Equipment, int Location,
	                                     int & _numViolatedLocations,
	                                     int & _numViolatedCapcityUnits,
	                                     std::vector<int> & _UsedCapacity);


};

#endif
