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

	


	// Getter Methods
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
	unsigned int numViolatedLocations;
	double numViolatedCapcityUnits;
	
	// Convinience Fuctions for Fitness Calculations
	void CalculateCapacityViolations();
	
	// Convinience Functions for Copying Parameters
	void CopyProblem(GQAP & _problem);
};

#endif