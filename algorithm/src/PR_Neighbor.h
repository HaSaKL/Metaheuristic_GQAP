#ifndef PR_NEIGHBORHOOD_H
#define PR_NEIGHBORHOOD_H

#include "neighborhood/moIndexNeighbor.h"
#include "GQAP.h"

class PR_Neighbor: public moIndexNeighbor<GQAP, GQAP::Fitness> {
	
private:
	int equipment;
	int newLocation;

	void translate(unsigned int _key, GQAP& _solution, GQAP_Solution sol_target);

public:
	using moIndexNeighbor<GQAP, typename GQAP::Fitness>::key;
	
	void move(GQAP& _solution, GQAP_Solution sol_target);
	void move(GQAP& _solution);
	void getMove(int& _equipment, int& _newLocation, GQAP& _solution, GQAP_Solution sol_target);
};

#endif // PR_NEIGHBORHOOD_H
