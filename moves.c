


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"


/**
 * Checks all poits from a way to see if all are inside the table
 * @param  turist [main struct]
 * @return        [true in case that all points are inside the table]
 */
bool CheckAllPoints(UNICODE * turist)
{
	for(int i = 0; i < turist->passadeira_vermelha.num_pontos; i++)
	{
		if(check_Point_Inside_Table(turist->tabu, turist->passadeira_vermelha.points[i]))
			return false;

	}

	return true;
}
