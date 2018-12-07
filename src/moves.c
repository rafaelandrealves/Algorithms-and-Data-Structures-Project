


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "dijkstra.h"

#define PrintCombinMatrix 1

#define Cmp_Int_Path(A) (A > 0)

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
point getIpoint(Problema * turist, int i)
{
    return getCaminho(turist)->points[i];
}

point getIpointFromCaminho(caminho * way, int i)
{
    return way->points[i];
}

point * get_point_vector(caminho * move)
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
    point * vect_out = (point *) Checked_Malloc(getXSize(getTabuleiro(turist)) * getYSize(getTabuleiro(turist)) * sizeof(point));

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
 * [INIT_Value_Matrix description]
 * @param  number_of_points [description]
 * @return                  [description]
 */
caminho ** INIT_Path_Matrix(int number_of_points)
{
    caminho ** matrix = (caminho **) Checked_Malloc(number_of_points * sizeof(caminho *));

    for( int i = 0; i < number_of_points; i++)
    {
        matrix[i] = (caminho *)Checked_Malloc(number_of_points * sizeof(caminho));
    }
    return matrix;
}


/**
 * [Insert_Caminho description]
 * @param  insert                 [caminho a inserir]
 * @param  number_Total_of_points [num_pontos do caminho a inserir + num_pontos do antigo]
 * @param  old                    [caminho antigo, para juntar]
 * @param  points_to_insert       [num_pontos a inserir]
 * @return                        [description]
 */
caminho *Use_Caminho_PreCalculated(caminho *insert, int number_Total_of_points,caminho *old, int points_to_insert)
{
    caminho *new = (caminho *) Checked_Malloc(sizeof(caminho));
    point * Path = (point *)Checked_Malloc(number_Total_of_points * sizeof(point*));

    new->num_pontos = old->num_pontos;
    new->custo_total = old->custo_total;
    new->points = Path;
    for(int i = 0; i < old->num_pontos; i = i + 1 )
    {
        new->points[i] = old->points[i];
    }
    for(int i = 0; i < points_to_insert; i = i + 1)
    {
        new->points[new->num_pontos + i] = insert->points[i];
    }
    new->custo_total = new->custo_total + insert->custo_total;
    new->num_pontos = new->num_pontos + insert->num_pontos;

    return new;
}

void Insert_CaminhoInMatrix(caminho ** move_matrix, caminho * to_insert, int origin, int destiny)
{
    //move_matrix[origin][destiny] = *to_insert;
    move_matrix[origin][destiny].custo_total = to_insert->custo_total;
    move_matrix[origin][destiny].num_pontos = to_insert->num_pontos;
    printf("Custo: %d\n", move_matrix[origin][destiny].custo_total);
    printf("Num pontos: %d\n", move_matrix[origin][destiny].num_pontos);
}

void Clean_caminho(caminho * move)
{
    point invalid = {.x = -1, .y = -1};
    for(int i = 0; i < move->num_pontos; i = i + 1)
    {
        move->points[i] = invalid;
    }
}

/**
 * [Given some points gets the cheapest move with arbitrary order od points]
 * @param turist [main struct]
 * @param fp_out [file pointer]
 * @param argv   [description]
 */
void Execute_C_Variant(Problema * turist, FILE * fp_out) //ATENÃO CIDADE 43, SE 1 CAMINHO FOR INVÁLIDO, ELE SAÍ LOGO?
{
    bool first_time = true;

    point inicial_point, final_point;
    int pos_init_p = 0, pos_dest_p = 0;


    bool validity = CheckAllPoints(turist);
    if(validity == false)
    {
        WriteFileWithFailure(turist, fp_out);
        return;
    }


    caminho * best = (caminho *) Checked_Malloc(sizeof(caminho));
    best->points = (point *) Checked_Malloc(sizeof(point) * 30000);
    best->num_pontos = 0;
    best->custo_total = INFTY;

    int point_on_matrix = 0;
    int ponto = 0, num_pontos_combin = 0, linha = 0, No_Path = 0;

    caminho ** Path_matrix = INIT_Path_Matrix(turist->passeio.num_pontos);

    caminho * atual = (caminho *) Checked_Malloc(sizeof(caminho));

    atual->points = (point *) Checked_Malloc(sizeof(point) * 30000);
    atual->custo_total = 0;
    atual->num_pontos = 0;

    int ** PermutMatrix = get_Matrix_Variant_C(getNumPontos(turist) - 1);

    #if PrintCombinMatrix == 1
        printMatrix((void **) PermutMatrix, fact(getNumPontos(turist) - 1), getNumPontos(turist) - 1);
    #endif

    for( linha = 0; linha < fact(getNumPontos(turist) - 1); linha++)
    {
        printf("O caminho é %d \n\n\n\n\n\n",linha);
        inicial_point = getIpoint(turist, 0);
        pos_init_p = 0;

        for(ponto = 0; ponto < getNumPontos(turist) - 1; ponto++)
        {
            pos_dest_p = PermutMatrix[linha][ponto];
            printf("init - %d\t dest - %d\n", pos_init_p, pos_dest_p);

            final_point = getIpoint(turist, pos_dest_p);
            printf("\t\t O valor da soma do atual_custo toal + o proximo caminho é %d\n", atual->custo_total + Path_matrix[pos_init_p][pos_dest_p].custo_total);
            printf("\t\t O valor do best->custo %d\n",best->custo_total);
            if((Path_matrix[pos_init_p][pos_dest_p].custo_total > 0) && (atual->custo_total + Path_matrix[pos_init_p][pos_dest_p].custo_total) > best->custo_total)
            {
                printf("\t\tCusto na matriz é menor\n");
                No_Path = 1;
                break;
            }
            else if((Path_matrix[pos_init_p][pos_dest_p].custo_total > 0))
            {
                int total_pontos = Path_matrix[pos_init_p][pos_dest_p].num_pontos + atual->num_pontos;
                atual = Use_Caminho_PreCalculated(&Path_matrix[pos_init_p][pos_dest_p], total_pontos, atual, Path_matrix[pos_init_p][pos_dest_p].num_pontos);
                inicial_point = final_point;
                printf("\t\tUsa a matriz\n\n");
                continue;
            }
            DijkstraAlgoritm_C(turist, fp_out, inicial_point, final_point, atual, &num_pontos_combin, &No_Path);

            if( No_Path == 0 && Path_matrix[pos_init_p][pos_dest_p].custo_total == 0)
            {
                Insert_CaminhoInMatrix(Path_matrix, atual, pos_init_p, pos_dest_p);
                printf("\t\tInsere na matriz\n\n");
            }
            if(No_Path == 1)
            {
                break;
            }

            inicial_point = final_point;
            pos_init_p = pos_dest_p;
        }

        if(first_time == true && No_Path == 0)
        {
            best->num_pontos = atual->num_pontos;
            best->custo_total = num_pontos_combin;
        	best->points = atual->points;
            point_on_matrix = linha;
            first_time = false;
        }
        else if (No_Path == 0)
        {
            printf("\tO CUSTO TOTAL best %d\n\n",best->custo_total);
            printf("\tO CUSTO TOTAL ATUAL %d\n\n",atual->custo_total);
            if(atual->custo_total < best->custo_total)
            {
                point_on_matrix = linha;
                best->custo_total = atual->custo_total;
                best->num_pontos = num_pontos_combin;

                printf("\tO num_pontos_combin--%d o custo---%d\n\n\n\n\n\n",best->num_pontos, atual->custo_total);
                Clean_caminho(best);
                best->points = Copy_Caminho(atual->points, num_pontos_combin);

            }
        }
        atual->custo_total = 0;
        atual->num_pontos = 0;
        Clean_caminho(atual);
        num_pontos_combin = 0;
        No_Path = 0;
    }

    if(first_time == true)
        WriteFileWithFailure(turist, fp_out);
    else
        OutPUT_C(getIpoint(turist, PermutMatrix[point_on_matrix][ponto]), getIpoint(turist, 0), turist, fp_out,best->num_pontos, best);

    free(atual->points);
    free(best);
    free(atual);

}


/**
 * [Copy_Caminho description]
 * @param  path       [description]
 * @param  num_pontos [description]
 * @return            [description]
 */
point * Copy_Caminho(point * path, int num_pontos)
{
    point * new = (point *) malloc(30000 * sizeof(point));

    for(int i = 0; i < num_pontos && path[i].x != -1 && path[i].y != -1; i = i + 1)
    {
        new[i] = path[i];
    }
    return new;

}

/**
 * [Aux_Set_Point description]
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
