#ifndef PR_NEIGHBORHOOD_H
#define PR_NEIGHBORHOOD_H

#include "neighborhood/moIndexNeighbor.h"
#include "GQAP.h"

class PR_Neighbor: public moIndexNeighbor<GQAP, GQAP::Fitness> {
	
private:
	int equipment;
	int newLocation;

	void translate(unsigned int _key, GQAP_Solution sol_target, GQAP_Solution sol_start);

public:
	using moIndexNeighbor<GQAP, typename GQAP::Fitness>::key;
	void move(GQAP_Solution sol_target, GQAP & _solution);
	void getMove(int & _equipment, int & _newLocation, GQAP_Solution sol_target, GQAP & _solution);
};

#endif // PR_NEIGHBORHOOD_H