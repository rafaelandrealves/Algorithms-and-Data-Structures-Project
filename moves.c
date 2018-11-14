


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"



struct caminho_t
{
    int num_pontos;
    point * points;
    int custo_total;
};

struct Problema_t // main struct of the program
{
    char modo_jogo; // problem mode
    tabuleiro tabu; // table
    caminho passadeira_vermelha; // move that ir read from the file
    // caminho * para_preguicosos;  // possible ways to be the optimal soluction
};

tabuleiro getTabuleiro(Problema * turist)
{
	return turist->tabu;
}


caminho getCaminho(Problema * turist)
{
	return turist->passadeira_vermelha;
}

int getCustoTotal(Problema * turist)
{
	return getCaminho(turist).custo_total;
}


int getNumPontos(Problema * turist)
{
	return getCaminho(turist).num_pontos;
}


/**
 * Checks all poits from a way to see if all are inside the table
 * @param  turist [main struct]
 * @return        [true in case that all points are inside the table]
 */
bool CheckAllPoints(Problema * turist)
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
 * @param turist [main struct]
 * @param fp_out [output file pointer ]
 */
void Execute_B_Variant(Problema * turist, FILE * fp_out)
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
				WriteFileWithFailure(turist, fp_out);
				return;
			}
		}
	}
	else
	{
		// write file with failure because one (or more) point(s) aren't inside the matrix or are
		WriteFileWithFailure(turist, fp_out);
		return;
	}

	// write file with success with the cost of the movement
	WriteFileWithSuccess(turist, fp_out);
}

/**
 * Given one point it gets the cheapest point to reach with just one move
 * @param turist [main struct]
 * @param fp_out [output file pointer to]
 */
void Execute_A_Variant(Problema * turist, FILE * fp_out)
{
 	bool sign = false;
	sign = CheckAllPoints(turist);

	if(sign == false)
		WriteFileWithFailure(turist, fp_out);
	else
	{
		movimentos(turist);
		if(turist->passadeira_vermelha.custo_total != 0)
			WriteFileWithSuccess(turist, fp_out);
		else
			WriteFileWithFailure(turist, fp_out);

		sign = false;
	}
}

Problema * Alloc_Problema(int sizey, int sizex, char game_mode, int points_num)
{
	Problema * new = (Problema *) Checked_Malloc(sizeof(Problema));
	turist->tabu = Set_Lenght_Width(&(turist->tabu), sizey, sizex);
	turist->passadeira_vermelha.points = (point *) Checked_Malloc( new->passadeira_vermelha.num_pontos * sizeof(point));
	turist->modo_jogo = game_mode;

	turist->passadeira_vermelha.num_pontos = points_num;

	return turist;
}

void Aux_Set_Point(Problema * turist, int x, int y, int i)
{
	SetPoint(&(turist->passadeira_vermelha.points[i]), x, y, i);
}

void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx)
{
	SetMatrixElement(&(turist->tabu.tab), cost, yy, xx);
}

char GetModoJogo(Problema * turist)
{
	return turist->game_mode;
}


/**
 * Free all memory from one struct
 * @param turista [struct to be freed]
 */
void FreeAll(Problema * turista)
{
    // fazer free do caminho lido do ficheiro
    free(turista->passadeira_vermelha.points);

    for(int i = 0; i < turista->tabu.size_y; i = i + 1)
        free(turista->tabu.tab[i]);

    free(turista->tabu.tab);

    free(turista);
}


/**
 * Prints all the info of one struct the way it was read
 * @param turista [struct to be printed]
 */
void PrintMainStruct(Problema * turista)
{
    printf("%d %d %c %d\n", turista->tabu.size_y, turista->tabu.size_x, turista->modo_jogo, turista->passadeira_vermelha.num_pontos);

    for(int i = 0; i < turista->passadeira_vermelha.num_pontos; i = i + 1)
        printf("%d %d\n", get_Y_From_Point(turista->passadeira_vermelha.points[i]), get_X_From_Point(turista->passadeira_vermelha.points[i]));

    for(int yy = 0; yy < turista->tabu.size_y; yy = yy + 1)
    {
        printf("\t");
        for(int xx = 0; xx < turista->tabu.size_x; xx = xx + 1)
            printf("%d ", GetPointCostFromCoord(yy, xx));

        printf("\n");
    }

}

//Função encarregue de fazer os movimentos para todos os lados possiveis e ver qual é que é mais barato
/*
 PARAM:
  -> NEW: Matriz com os dados da matriz
*/
void movimentos(Problema *new)
{
    char variavelx = 'x';
    char variavely = 'y';
    new->passadeira_vermelha.custo_total = 10000;

    movimentos_num_ponto(new, new->tabu.size_x, new->tabu.size_y, get_X_From_Point(new->passadeira_vermelha.points[0]),
        get_Y_From_Point(new->passadeira_vermelha.points[0]) - 2, variavelx, &(new->passadeira_vermelha.custo_total)); //move_HIGH

    movimentos_num_ponto(new, new->tabu.size_x, new->tabu.size_y, get_X_From_Point(new->passadeira_vermelha.points[0]),
        get_Y_From_Point(new->passadeira_vermelha.points[0]) + 2, variavelx, &(new->passadeira_vermelha.custo_total)); //move_LOW

    movimentos_num_ponto(new, new->tabu.size_x, new->tabu.size_y, get_X_From_Point(new->passadeira_vermelha.points[0]) + 2,
        get_Y_From_Point(new->passadeira_vermelha.points[0]), variavely, &(new->passadeira_vermelha.custo_total)); //move_low_right

    movimentos_num_ponto(new, new->tabu.size_x, new->tabu.size_y, get_X_From_Point(new->passadeira_vermelha.points[0]) - 2,
        get_Y_From_Point(new->passadeira_vermelha.points[0]), variavely, &(new->passadeira_vermelha.custo_total)); //move_low_left

    if(new->passadeira_vermelha.custo_total == 10000)
        new->passadeira_vermelha.custo_total = 0;
}
