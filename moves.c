


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
		if((check_Point_Inside_Table(turist->tabu, turist->passadeira_vermelha.points[i]) == false) ||
		(GetPointCost(turist->tabu, turist->passadeira_vermelha.points[i]) == 0))
			return false;
	}

	return true;
}

/**
 * Given some points checks if it is a valid move which means if all points are valid
 * 	are accesible and only make horse jumps
 * @param turist [description]
 * @param fp_out [description]
 */
void Execute_B_Variant(UNICODE * turist, FILE * fp_out)
{
	int validity = 0;

	// means that one or more points aren't inside the table or are inaccessible
	if(!CheckAllPoints(turist))
		validity = -1;

	if(validity) // if all points are valid program will check if all make horse jumps
	{
		
	}

}
