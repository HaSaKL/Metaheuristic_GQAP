#include "GRASP_FixedAlpha.h"

// Set the alpha value depending on the provided parameter
GRASP_FixedAlpha::GRASP_FixedAlpha(double _alpha) {
	alpha = _alpha;
}

void GRASP_FixedAlpha::init(GQAP & _p) {
	
}

double GRASP_FixedAlpha::operator() (GQAP & _p) {
	return alpha;
}