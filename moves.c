


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
	bool validity = false;

	// means that one or more points aren't inside the table or are inaccessible
	validity = CheckAllPoints(turist);

	if(validity == true) // if all points are valid program will check if all make horse jumps
	{
		for(int i = 1; i < turist->passadeira_vermelha.num_pontos; i++)
		{
			if(CheckHorseJump(turist->passadeira_vermelha.points[i-1], turist->passadeira_vermelha.points[i]))
			{
				turist->passadeira_vermelha.custo_total += GetPointCost(turist->tabu, turist->passadeira_vermelha.points[i]);
			}
			else
			{
				// write file with failure because one (or more) point(s) does not have the horse jump move
				printf("%d %d %c %d -1 0\n\n", turist->tabu.size_y, turist->tabu.size_x, turist->modo_jogo, turist->passadeira_vermelha.num_pontos);
				return;
			}
		}
	}
	else
	{
		// write file with failure because one (or more) point(s) aren't inside the matrix or are
		printf("%d %d %c %d -1 0\n\n", turist->tabu.size_y, turist->tabu.size_x, turist->modo_jogo, turist->passadeira_vermelha.num_pontos);
		return;
	}

	// write file with success with the cost of the movement
	printf("%d %d %c %d 1 %d\n\n", turist->tabu.size_y, turist->tabu.size_x, turist->modo_jogo, turist->passadeira_vermelha.num_pontos, turist->passadeira_vermelha.custo_total);


}
