/* Test Program to Test If Problem Data can be Read correctly */

#include <iostream>
#include <string>
#include "GQAP.h"

int main(int argc, char* argv[]) {
	try {
		std::cout << "Metaheuristic for the GQAP compiled at " << __DATE__ << " " << __TIME__;
		std::cout << "Test To Read Problem Data" << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
		
		std::cout << "Loading Problem ... ";
		
		std::string fileName = "../../../test_instances/from_literature/original_format/cordeau/20-15-35.txt";
		std::cout << fileName << std::endl;
		
		GQAP GQAP(fileName);
		
		std::cout << "... loaded. " << std::endl << std::endl;
		
		std::cout << "Problem Dimensions: " << std::endl;
		std::cout << "Number of Locations: " << GQAP.GetNumLocation() << std::endl;
		std::cout << "Number of Equipment: " << GQAP.GetNumEquip() << std::endl;
		std::cout << "Transport Costs: " << GQAP.GetTransportCost() << std::endl;
		std::cout << std::endl;
		std::cout << "Flow [1,2]: " << GQAP.GetMatrixFlow(1,2) << std::endl;
		std::cout << "Flow [3,2]: " << GQAP.GetMatrixFlow(3,2) << std::endl;
		std::cout << std::endl;
		std::cout << "Distance [3,1]: " << GQAP.GetMatrixDist(3,1) << std::endl;
		std::cout << "Distance [0,4]: " << GQAP.GetMatrixDist(0,4) << std::endl;
		std::cout << std::endl;
		std::cout << "Installation Cost [1,3]: " << GQAP.GetMatrixInstallCost(1,3) << std::endl;
		std::cout << "Installation Cost [4,2]: " << GQAP.GetMatrixInstallCost(4,2) << std::endl;
		std::cout << std::endl;
		std::cout << "Space Requirement of 3: " << GQAP.GetVectorSpaceReq(3) << std::endl;;
		std::cout << "Space Capacity @ 2: " << GQAP.GetVectorSpaceCap(2) << std::endl;;
		std::cout << std::endl;
	} 
	catch(std::exception& e) {
		std::cout << "Expectation cought: ";
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}