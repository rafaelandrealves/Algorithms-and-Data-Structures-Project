


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "dijkstra.h"

#define PrintCombinMatrix 0

struct caminho_t
{
    int num_pontos;
    point ** points; // points pointer vector
    int custo_total;
};

struct Problema_t // main struct of the program
{
    char modo_jogo; // problem mode
    tabuleiro * tabu; // table
    struct caminho_t passeio; // move that ir read from the file
};

#include "moves.h"

/**
 * Function that obtains a struct tabuleiro of a struct Problema
 * @param  turist [Struct Problema]
 * @return        [Pointer to struct tabuleiro]
 */
tabuleiro * getTabuleiro(Problema * turist)
{
	return (turist->tabu);
}

/**
 * Function that obtains a pointer to a struct caminho from struct Problema
 * @param  turist [Struct Problema]
 * @return        [Pointer to struct caminho]
 */
caminho * getCaminho(Problema * turist)
{
	return &(turist->passeio);
}

/**
 * Function that obtains the total cost of a certain struct Caminho
 * @param  turist [Struct Problema]
 * @return        [Value of the total cost of a struct caminho]
 */
int getCustoTotalFromProb(Problema * turist)
{
	return getCaminho(turist)->custo_total;
}

int getCustoTotalFromCaminho(caminho * way)
{
    return way->custo_total;
}

/**
 * Function that obtains the total number of points of a struct caminho
 * @param  turist [Struct problema]
 * @return        [Total number of points]
 */
int getNumPontos(Problema * turist)
{
	return getCaminho(turist)->num_pontos;
}

/**
 * Function that gets the i point of a certain path
 * @param  turist [Main struct Problema]
 * @param  i      [Index]
 * @return        [Pointer to point searched]
 */
point * getIpoint(Problema * turist, int i)
{
    return getCaminho(turist)->points[i];
}

point * getIpointFromCaminho(caminho * way, int i)
{
    return way->points[i];
}

point ** get_point_vector(caminho * move)
{
    return move->points;
}

caminho * Set_Custo_Total(caminho *move, int value)
{
    move->custo_total = value;
    return move;
}

/**
 * Checks all poits from a way to see if all are inside the table
 * @param  turist [main struct]
 * @return        [true in case that all points are inside the table]
 */
bool CheckAllPoints(Problema * turist)
{
	for(int i = 0; i < getNumPontos(turist); i++)
	{
			if((check_Point_Inside_Table(turist->tabu, turist->passeio.points[i]) == false) ||
			(GetPointCostFromPoint(turist->tabu, turist->passeio.points[i]) == 0))
			return false;
	}

	return true;
}



void Free_Point_Vec(int num, caminho * move_struct)
{
    //printf("olaaa\n");
    for (int i = 0 ; i < num; i++)
    {
        free(getIpointFromCaminho(move_struct, i));
    }
    free(get_point_vector(move_struct));

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
    int index = 0;
    int pontos_atuais = 0;
    int numMalloc = 2000;
    point ** vect_out = (point **) Checked_Malloc(numMalloc * sizeof(point *));

    caminho * move_struct = (caminho *) Checked_Malloc(sizeof(caminho));
    move_struct->num_pontos = 0;
    move_struct->points = vect_out;
    move_struct->custo_total = 0;


	// means that one or more points aren't inside the table or are inaccessible
	validity = CheckAllPoints(turist);

	if(validity == true) // if all points are valid program will check if all make horse jumps
	{
		for(int i = 0; i < turist->passeio.num_pontos - 1; i++)
		{
            if((numMalloc - index) <= 1000) // é necessário alocar mais memória
            {
                numMalloc *= 2;
                move_struct->points = (point **) realloc(move_struct->points, numMalloc * sizeof(point *));
            }
            DijkstraAlgoritm_B(turist, fp_out, turist->passeio.points[i], turist->passeio.points[i + 1], &index, &pontos_atuais, move_struct);
		}
	}
	else
	{
		// write file with failure because one (or more) point(s) aren't inside the matrix
		WriteFileWithFailure(turist, fp_out);
	}

    Free_Point_Vec(index, move_struct);
    free(move_struct);
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
        DijkstraAlgoritm_A(turist, fp_out, turist->passeio.points[0], turist->passeio.points[1]);

}


void SetMatrix_Variant_C(int ** matriz, int * vetor, int num_ele, int num_linha)
{
    for(int i = 0; i < num_ele; i++)
        matriz[num_linha][i] = vetor[i];
}


void troca_int(int * str, int p1, int p2)
{
  int tmp;
  tmp = str[p1];
  str[p1] = str[p2];
  str[p2] = tmp;
}


void permutacao_recursiva(int * vetor, int ** matriz, int k, int num_ele, int *num_linha)
{
    int i;
    int * copia_vetor = vetor;

    if (k == num_ele)
    {
        SetMatrix_Variant_C(matriz, vetor, num_ele, *num_linha);
        (*num_linha)++;
        // print_vector(vetor, num_ele);
    }

    else
    {
        for (i = k; i < num_ele; i++)
        {
            troca_int(copia_vetor, k, i);
            permutacao_recursiva(vetor, matriz, k + 1, num_ele, num_linha);
            troca_int(copia_vetor, i, k);
        }
    }
}


int ** get_Matrix_Variant_C(int num_pontos)
{
    int num_linha = 0;
    int ** matrix = (int **) Checked_Malloc(sizeof(int*) * fact(num_pontos));
    for(int i = 0; i < fact(num_pontos); i++)
        matrix[i] = (int *) Checked_Malloc(sizeof(int) * (num_pontos));

    int * vetor = (int *) calloc(sizeof(int), (num_pontos));
    for(int i = 0; i < num_pontos; i++)
        vetor[i] = i + 1;

    permutacao_recursiva(vetor, matrix, 0, num_pontos, &num_linha);

    free(vetor);

    return matrix;
}

void Free_Matrix_Variant_C(int ** matrix, int num_pontos)
{
    for(int i = 0; i < num_pontos; i++)
        free(matrix[i]);

    free(matrix);
}


/**
 * [Given some points gets the cheapest move with arbitrary order od points]
 * @param turist [main struct]
 * @param fp_out [file pointer]
 * @param argv   [description]
 */
void Execute_C_Variant(Problema * turist, FILE * fp_out)
{
    bool first_time = true;

    point * inicial_point = NULL;

    caminho * best = (caminho *) Checked_Malloc(sizeof(caminho));
    best->custo_total = 0;
    best->num_pontos = 0;
    // best->points = (point **) Checked_Malloc(sizeof(point *) * 3000);

    caminho *atual = (caminho *) Checked_Malloc(sizeof(caminho));
    atual->custo_total = 0;
    atual->num_pontos = 0;

    bool validity = CheckAllPoints(turist);
    if(validity == false)
    {
        WriteFileWithFailure(turist, fp_out);
        free(best);
        free(atual);
        return;
    }

    int ** PermutMatrix = get_Matrix_Variant_C(getNumPontos(turist) - 1);
    #if PrintCombinMatrix == 1
        printMatrix((void **) PermutMatrix, fact(getNumPontos(turist) - 1), getNumPontos(turist) - 1);
    #endif

    for(int linha = 0; linha < fact(getNumPontos(turist) - 1); linha++)
    {
        atual->points = (point **) Checked_Malloc(sizeof(point *) * 3000);
        inicial_point = getIpoint(turist, 0);
        for(int ponto = 0; ponto < getNumPontos(turist) - 1; ponto++)
        {
            point * final_point = getIpoint(turist, PermutMatrix[linha][ponto]);
            DijkstraAlgoritm_C(turist, fp_out, inicial_point, final_point, atual);
            inicial_point = final_point;
        }
        if(first_time == true)
        {
            best->num_pontos = atual->num_pontos;
            best->custo_total = atual->custo_total;
        	best->points = atual->points;
            first_time = false;
        }
        else
        {
            if(atual->custo_total < best->custo_total)
            {
                best->custo_total = atual->custo_total;
                best->num_pontos = atual->num_pontos;
                // free(best->num_pontos = atual->points);
                best->points = atual->points;
            }
        }
        atual->custo_total = 0;
        atual->num_pontos = 0;
        free(atual->points);

    }



    Free_Matrix_Variant_C(PermutMatrix, getNumPontos(turist) - 1);
    free(atual);
    free(best);
}


/**
 * [Allocs memory for the Problema struct]
 * @param  sizey      [y size of the board]
 * @param  sizex      [x size of the board]
 * @param  game_mode  [mode of game]
 * @param  points_num [number of points from the move vector]
 * @return            [returns the problem allocated]
 */
Problema * Alloc_Problema(int sizey, int sizex, char game_mode, int points_num)
{
	Problema * turist = (Problema *) Checked_Malloc(sizeof(Problema));
    turist->tabu = (tabuleiro *) Checked_Malloc(getSizeOfTabuleiro());
	turist->tabu = Set_Lenght_Width(turist->tabu, sizey, sizex);
    turist->passeio.num_pontos = points_num;
	turist->passeio.points = (point **) Checked_Malloc( getNumPontos(turist) * getSizeOfPointAst());
    turist->modo_jogo = game_mode;

	return turist;
}

/**
 * Function that allocates memory for a point to be added in the path
 * @param turist [Struct Problema]
 * @param x      [x of point to be added]
 * @param y      [y of point to be added]
 * @param i      [Index]
 */
void Aux_Set_Point(Problema * turist, int x, int y, int i)
{
    turist->passeio.points[i] = (point *) Checked_Malloc(getSizeOfPoint());
    SetPoint(turist->passeio.points[i], x, y);
}

/**
 * [Aux_Set_Matrix_Element description]
 * @param turist [description]
 * @param cost   [description]
 * @param yy     [description]
 * @param xx     [description]
 */
void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx)
{
	SetMatrixElement(turist->tabu, cost, yy, xx);
}

/**
 * Function that gets the mode of a certain problem
 * @param  turist [Main struct Problema]
 * @return        [Game mode]
 */
char GetModoJogo(Problema * turist)
{
	return (turist->modo_jogo);
}


/**
 * Free all memory from one struct
 * @param turista [struct to be freed]
 */
void FreeAll(Problema * turista)
{
    // fazer free do caminho lido do ficheiro
    for(int j = 0; j < getNumPontos(turista); j++)
        free(turista->passeio.points[j]);

    free(turista->passeio.points);

    for(int i = 0; i < getYSize(turista->tabu); i = i + 1)
        free(getMatrixLinePointer(turista->tabu, i));

    free(getMatrixPointer(turista->tabu));
    free(getTabuleiro(turista));

    free(turista);
}


/**
 * Prints all the info of one struct the way it was read
 * @param turista [struct to be printed]
 */
void PrintMainStruct(Problema * turista)
{
    printf("%d %d %c %d\n", getYSize(turista->tabu), getXSize(turista->tabu), GetModoJogo(turista), getNumPontos(turista));

    for(int i = 0; i < getNumPontos(turista); i = i + 1)
        printf("%d %d\n", get_Y_From_Point(turista->passeio.points[i]), get_X_From_Point(turista->passeio.points[i]));

    for(int yy = 0; yy < getYSize(turista->tabu); yy = yy + 1)
    {
        printf("\t");
        for(int xx = 0; xx < getXSize(turista->tabu); xx = xx + 1)
            printf("%d ", GetPointCostFromCoord(turista->tabu, yy, xx));

        printf("\n");
    }

}


/**
 * Writes the file with the failure
 * @param cavaleiro [main struct]
 * @param NULL      [file pointer]
 */
void WriteFileWithFailure(Problema * turist, FILE * fp_out)
{
    fprintf(fp_out, "%d %d %c %d -1 0\n\n", getYSize(turist->tabu), getXSize(turist->tabu), GetModoJogo(turist), getNumPontos(turist));
}

/**
 * Wirtes the file with success
 * @param turist [main struct]
 * @param fp_out [file pointer]
 */
void WriteFileWithSuccess(Problema * turist, FILE * fp_out)
{
    fprintf(fp_out, "%d %d %c %d 1 %d\n\n", getYSize(turist->tabu), getXSize(turist->tabu), GetModoJogo(turist), getNumPontos(turist), getCustoTotalFromProb(turist));
}
