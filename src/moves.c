
/******************************************************************************
 *
 * File Name: moves.c

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  11 Dez 2018
 *
 * NAME
 *     moves.c - Functions related with one move. The main and auxiliary functions to execute the A, B and C variant. 
 *
*/


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "dijkstra.h"

#define PrintCombinMatrix 0

#define INFTY 9999

struct caminho_t
{
    int num_pontos;
    point * points; // points pointer vector
    short custo_total;
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


/**
 * [Set the matrix element ]
 * @param turist [main struct]
 * @param cost   [cost of the point]
 * @param yy     [y coordinates]
 * @param xx     [x coordinates]
 */
void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx)
{
	SetMatrixElement(turist->tabu, cost, yy, xx);
}

/**
 * [Auxiliary function to set one point with x and y coordinates]
 * @param turist [description]
 * @param i      [description]
 * @param x      [description]
 * @param y      [description]
 */
void Aux_Set_Point(Problema * turist, int i, int x, int y)
{
    SetPoint(&(turist->passeio.points[i]), x, y);
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
 * [getCustoTotalFromCaminho description]
 * @param  way [description]
 * @return     [description]
 */
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
 * [Gets the cost of one entire combination with the vector of pointers to single jump paths]
 * @param  move [vector of caminho *]
 * @return      [cost of one combination]
 */
int GetCostFromOnePath(caminho ** move)
{
    int custo = 0;

    for (int i = 0; move[i] != NULL; i++)
    {
        custo += move[i]->custo_total;
    }
    return custo;
}

/**
 * [Given one move returns the number of points that it contains]
 * @param  move [represents the move]
 * @return      [number of poitns]
 */
int getNumPontosFromCaminho(caminho *move)
{
	return move->num_pontos;
}


/**
 * Function that gets the i point of a certain path
 * @param  turist [Main struct Problema]
 * @param  i      [Index]
 * @return        [Pointer to point searched]
 */
point getIpoint(Problema * turist, int i)
{
    return getCaminho(turist)->points[i];
}

/**
 * Get the 'i' point from one Path_Matrix
 * @param  way [path struct]
 * @param  i   [position of the point]
 * @return     [point with the 'i' index]
 */
point getIpointFromCaminho(caminho * way, int i)
{
    return way->points[i];
}

/**
 * [Get the pointer to the points vector inside the path struct]
 * @param  move [path struct]
 * @return      [pointer to the point vector]
 */
point * get_point_vector(caminho * move)
{
    return move->points;
}

/**
 * [Set the cost of one path ]
 * @param  move  [path to set its cost]
 * @param  value [value of the cost to be set]
 * @return       [path set]
 */
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


/**
 * [Frees the memory related with the path struct]
 * @param move_struct [path struct]
 */
void Free_Point_Vec(caminho * move_struct)
{
    free(get_point_vector(move_struct));
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


/**
 * Given some points checks if it is a valid move which means if all points are valid
 * 	are accesible and only make horse jumps
 * @param turist [main struct]
 * @param fp_out [output file pointer]
 */
void Execute_B_Variant(Problema * turist, FILE * fp_out)
{
	bool validity = false;
    int index = 0;
    int pontos_atuais = 0;
    point * vect_out = (point *) Checked_Malloc(getXSize(getTabuleiro(turist)) * getYSize(getTabuleiro(turist)) * sizeof(point));

    caminho * move_struct = (caminho *) Checked_Malloc(sizeof(caminho));
    move_struct->num_pontos = 0;
    move_struct->points = vect_out;
    move_struct->custo_total = 0;


	// means that one or more points aren't inside the table or are inaccessible
	validity = CheckAllPoints(turist);

	if(validity == true) // if all points are valid program will check if all make horse jumps
	{
        // executes the Dijkstra for each 2 pair of points
		for(int i = 0; i < turist->passeio.num_pontos - 1; i++)
		{
            DijkstraAlgoritm_B(turist, fp_out, turist->passeio.points[i], turist->passeio.points[i + 1], &index, &pontos_atuais, move_struct);
		}
	}
	else
	{
		// write file with failure because one (or more) point(s) aren't inside the matrix
		WriteFileWithFailure(turist, fp_out);
	}

    Free_Point_Vec(move_struct);
    free(move_struct);
}


/**
 * [Given one path it calculates the cheapest path changing the order of the turist points]
 * @param turist [struct with the information read from the file]
 * @param fp_out [file pointer to the output file]
 */
void Execute_C_Variant(Problema * turist, FILE * fp_out)
{
    bool validity = CheckAllPoints(turist);
    if(validity == false)
    {
        WriteFileWithFailure(turist, fp_out);
        return;
    }
    bool No_Path = false;


    // auxiliary vector to compute all the path combinations
    // printf("num pontos: %d\n", turist->passeio.num_pontos);
    int * vetor_combinacoes = (int *) Checked_Malloc(sizeof(int) * (turist->passeio.num_pontos - 1));
    for(int i = 0; i < turist->passeio.num_pontos - 1; i++)
        vetor_combinacoes[i] = i + 1;

    // vector that contains pointers to path in each position
    caminho ** best = (caminho **) Checked_Malloc(sizeof(caminho*) *  turist->passeio.num_pontos);

    // vector that contains pointers to path in each position
    caminho ** atual = (caminho **) Checked_Malloc(sizeof(caminho*) * turist->passeio.num_pontos);
    for( int i = 0; i < turist->passeio.num_pontos - 1 ; i++)
    {
        best[i] = NULL;
        atual[i]= NULL;
    }


    caminho * move_to_save = (caminho *) Checked_Malloc(sizeof(caminho));
    move_to_save->num_pontos = 0;
    move_to_save->custo_total = 0;
    move_to_save->points = (point *) Checked_Malloc(sizeof(point) * 10000);

    caminho ** Path_matrix = INIT_Path_Matrix(turist->passeio.num_pontos);
    bool first_time = true;


    caminhos_recursiva(vetor_combinacoes, turist, 0, Path_matrix, best,atual, &first_time, move_to_save, &No_Path);



    if(first_time == true && No_Path == true)
        WriteFileWithFailure(turist, fp_out);
    else
        OutPUT_C(turist, fp_out, best);


    Free_INIT_Path_Matrix(Path_matrix,turist->passeio.num_pontos);
    free(vetor_combinacoes);
    free(best);
    free(atual);
    free(move_to_save->points);
    free(move_to_save);
}

/**
 * [generates each combination on the turist points and compute the DIjkstra algorithm to get the cheapest path for that combination]
 * @param vetor_combi  [vector of the combinations]
 * @param turist       [struct of the problem]
 * @param k            [description]
 * @param Path_Matrix  [saves the path from one single jump path]
 * @param best         [best path]
 * @param atual        [current path]
 * @param first_time   [checks if it is the first time that the problem is computed]
 * @param move_to_save [path to save the single jump path in the Path_Matrix]
 * @param No_Path      [checks is there is no path on this combination]
 */
void caminhos_recursiva(int * vetor_combi, Problema * turist, int k, caminho ** Path_Matrix, caminho ** best, caminho **atual, bool * first_time, caminho * move_to_save, bool *No_Path)
{
    int i;
    int * copia_vetor_combi = vetor_combi;
    if(*No_Path == true)
        return;

    if ( k == turist->passeio.num_pontos - 1)
    {
        // executes the Dijkstra for this path combination
        C_for_one_path(turist, vetor_combi, Path_Matrix, first_time, best,atual, move_to_save,No_Path);
        if(*No_Path == true)
            return;
    }
    else
    {
        for (i = k; i < turist->passeio.num_pontos - 1; i++)
        {
            troca_int(copia_vetor_combi, k, i);
            caminhos_recursiva(vetor_combi, turist, k + 1, Path_Matrix, best,atual,first_time, move_to_save,No_Path);
            troca_int(copia_vetor_combi, i, k);
        }
    }
}


/**
 * [exchange 2 integers]
 * @param str [int vector]
 * @param p1  [position 1 of vector]
 * @param p2  [position 2 of vector]
 */
void troca_int(int * str, int p1, int p2)
{
  int tmp;
  tmp = str[p1];
  str[p1] = str[p2];
  str[p2] = tmp;
}


/**
 * [Allocs and inicializes the path matrix to ]
 * @param  number_of_points [number of points in the path]
 * @return                  [path matrix allocated and inicialized]
 */
caminho ** INIT_Path_Matrix(int number_of_points)
{
    caminho ** matrix = (caminho **) Checked_Malloc(number_of_points * sizeof(caminho *));

    for( int i = 0; i < number_of_points; i++)
    {
        matrix[i] = (caminho *) Checked_Malloc(number_of_points * sizeof(caminho));
        for(int j = 0; j < number_of_points; j++)
        {
            matrix[i][j].points = (point *) Checked_Malloc(sizeof(point) * 20000);
        }

    }
    return matrix;
}

/**
 * [Free_INIT_Path_Matrix description]
 * @param Path_Matrix [description]
 * @param num_points  [description]
 */
void Free_INIT_Path_Matrix(caminho ** Path_Matrix, int num_points)
{
    for(int i = 0; i < num_points; i = i + 1)
    {
        for(int j = 0; j < num_points; j = j + 1)
            free(Path_Matrix[i][j].points);

        free(Path_Matrix[i]);
    }
    free(Path_Matrix);
}


/**
 * [Inserts one single jump path in the Path_Matrix]
 * @param move_matrix [matrix with all the paths]
 * @param to_insert   [path to insert in the matrix]
 * @param origin      [origin index of the matrix]
 * @param destiny     [destiny index of the matrix]
 */
void Insert_CaminhoInMatrix(caminho ** move_matrix, caminho * to_insert, int origin, int destiny)
{
    for(int i = 0; i < to_insert->num_pontos; i++)
    {
        move_matrix[origin][destiny].points[i] = to_insert->points[i];
    }

    //printf("O custo-total %d\n",to_insert->custo_total);
    move_matrix[origin][destiny].custo_total = to_insert->custo_total;
    move_matrix[origin][destiny].num_pontos = to_insert->num_pontos;
}


/**
 * [C_for_one_path description]
 * @param turist       [struct with the info read from the file]
 * @param comb_vector  [current combination]
 * @param Path_matrix  [matrix with thesingle jump paths]
 * @param first_time   [variable to check if it is the first time]
 * @param best         [path of the best combination]
 * @param atual        [path of the current combination]
 * @param move_to_save [path of one single jump (A->B) to save in the path matrix if necessary]
 * @param No_Path      [variable to check if there is a possible path]
 */
void C_for_one_path(Problema * turist, int * comb_vector, caminho ** Path_matrix, bool * first_time, caminho ** best,caminho ** atual, caminho * move_to_save, bool * No_Path)
{
    int pos_init_p = 0, pos_dest_p, custo_acumulado = 0, not_better_path = 0;
    point final_point, inicial_point;

    inicial_point = getIpoint(turist, 0);
    for(int ponto = 0; ponto < getNumPontos(turist) - 1; ponto++)
    {
        // access the combination vector to check the index of final point
        pos_dest_p = comb_vector[ponto];

        //printf("\tCaminho de %d para %d\n", pos_init_p, pos_dest_p);

        final_point = getIpoint(turist, pos_dest_p);

        move_to_save->custo_total = 0;
        move_to_save->num_pontos = 0;

        // Branching!! If the cost of the current path is higher than the best path is not worth it to calculate it and can go
        // to the next combination (break the for loop)
        if((Path_matrix[pos_init_p][pos_dest_p].custo_total > 0) && (custo_acumulado + Path_matrix[pos_init_p][pos_dest_p].custo_total) > GetCostFromOnePath(best))
        {
            //printf("\t\tBranchingggg\n");
            not_better_path = 1;
            break;
        }

        // if the move to calculate is already saved in the path matrix it will load it and won't execute the Dijkstra
        if((Path_matrix[pos_init_p][pos_dest_p].custo_total > 0))
        {
            atual[ponto] = &Path_matrix[pos_init_p][pos_dest_p];

            custo_acumulado = custo_acumulado + atual[ponto]->custo_total;
            //printf("\t\tFui buscar à matriz com --%d-- pontos com --%d-- custo\n", atual->num_pontos, Path_matrix[pos_init_p][pos_dest_p].custo_total);
            inicial_point = final_point;
            pos_init_p = pos_dest_p;
            continue;
        }
        int num_points = 0;

        DijkstraAlgoritm_C(turist, inicial_point, final_point, move_to_save, &num_points, No_Path);

        // refresh the number of points in the path to save in the matrix
        move_to_save->num_pontos = num_points;
        if(*No_Path == true)
            break;

        // will save the current path in the Path Matrix and will also insert the reverse
        if( not_better_path == 0 && Path_matrix[pos_init_p][pos_dest_p].custo_total == 0 )
        {
            Insert_CaminhoInMatrix(Path_matrix, move_to_save, pos_init_p, pos_dest_p);
            atual[ponto] = &Path_matrix[pos_init_p][pos_dest_p];
            custo_acumulado = custo_acumulado + atual[ponto]->custo_total;
            Insert_Reverse_Move(move_to_save, Path_matrix, GetPointCostFromPoint(getTabuleiro(turist), final_point),
                                GetPointCostFromPoint(getTabuleiro(turist), inicial_point), inicial_point, pos_init_p, pos_dest_p);

            //printf("\t\tInseri na matriz\n");
        }
        if(not_better_path == 1)
        {
            break;
        }

        //printf("\t\tAtual depois do dijktra com  --%d-- pontos\n", atual->num_pontos);
        inicial_point = final_point;
        pos_init_p = pos_dest_p;
    }

    // if it is the first time will load the current path to the best path
    if(*first_time == true && not_better_path == 0 && *No_Path == false)
    {
        for(int i = 0; i < getNumPontos(turist) && atual[i] != NULL; i++)
        {
            best[i] = atual[i];
        }
        *first_time = false;
    }
    // oterwise the best path will only be changed when it finds a better path
    else if (not_better_path == 0 && *No_Path == false)
    {
        if(custo_acumulado < GetCostFromOnePath(best))
        {
            // load the path
            for(int i = 0; i < getNumPontos(turist) && atual[i] != NULL; i++)
            {
                best[i] = atual[i];
            }
        }
    }
    // reset the current path with NULL
    for( int i = 0; i < getNumPontos(turist);i++)
        atual[i] = NULL;
}

/**
 * [Insert the inverse move in the path matrix]
 * @param to_go               [path move to go A->B]
 * @param caminho_path_matrix [path matrix]
 * @param cost_final_to_go    [cost of final point in the to_go move]
 * @param cost_inicial_to_go  [cost of inicial point in the to_go move]
 * @param inicial_point_to_go [inicial point in the to_go move]
 * @param init_pos            [index of the inicial point to index the matrix]
 * @param dest_pos            [index of the final points to index the matrix]
 */
void Insert_Reverse_Move(caminho * to_go, caminho ** caminho_path_matrix, int cost_final_to_go, int cost_inicial_to_go, point inicial_point_to_go, int init_pos, int dest_pos)
{
    caminho_path_matrix[dest_pos][init_pos].custo_total = to_go->custo_total - cost_final_to_go + cost_inicial_to_go;
    caminho_path_matrix[dest_pos][init_pos].num_pontos = to_go->num_pontos;

    // set the number of points
    int num_pontos_to_go = to_go->num_pontos;

    // insert the points in the correct order
    for(int i = 0; i < to_go->num_pontos - 1; i = i + 1)
    {
        caminho_path_matrix[dest_pos][init_pos].points[i] = to_go->points[num_pontos_to_go - 2 - i];
    }
    // insert last point
    caminho_path_matrix[dest_pos][init_pos].points[num_pontos_to_go - 1] = inicial_point_to_go;

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
	turist->passeio.points = (point *) Checked_Malloc( getNumPontos(turist) * sizeof(point));
    turist->modo_jogo = game_mode;

	return turist;
}


/**
 * Free all memory from the main
 * @param turista [struct to be freed]
 */
void FreeAll(Problema * turista)
{
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
        printf("%d %d\n", turista->passeio.points[i].y, turista->passeio.points[i].x);

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
