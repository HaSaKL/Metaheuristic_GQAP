#ifndef GQAP_ELEMENTFLIP_NEIGHBOR_H
#define GQAP_ELEMENTFLIP_NEIGHBOR_H

#include "GQAP.h"
#include <neighborhood/moIndexNeighbor.h>
#include <cstdlib>  // for div_t and integer devision in translate function



// Specifies the ParadisEOs indexNeighbor-class for the GQAPs Flip-Index-Neighborhood
class GQAP_ElementFlipIndex_Neighbor: public moIndexNeighbor<GQAP, GQAP::Fitness> {
private:
	// A pair which represents the desired Flip-Operation:
	// to which new location should a given element be fliped to?
	// pair: <equipment index, new location index>
	std::pair<int, int> EquipmentToLocation;
	
	// function to translate an index to a corrseponding equipment-new location- pair
	void translate (unsigned int _key, GQAP & _solution);
	
public:
	using moIndexNeighbor<GQAP, typename GQAP::Fitness>::key;
	
	void move(GQAP & _solution);
	void getMove(int & _equipment, int & _newLocation, GQAP & _solution);
};

#endif // GQAP_ELEMENTFLIP_NEIGHBOR_H