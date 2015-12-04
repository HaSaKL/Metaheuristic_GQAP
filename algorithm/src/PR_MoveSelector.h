#ifndef PATH_RELINKING_MOVE_SELECTOR
#define PATH_RELINKING_MOVE_SELECTOR

#include "GQAP_Solution.h"
#include "GQAP_ElementFlip_IncrEval.h"

class PR_MoveSelector
{
public:
	virtual GQAP_Solution operator() (std::vector<GQAP_Solution> Moves);
};

#endif // PATH_RELINKING_MOVE_SELECTOR
