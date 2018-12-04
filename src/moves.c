


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
    int numMalloc = 500;
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
            if(index == numMalloc - 1)
            {
                numMalloc += 500;
                move_struct->points = (point **) realloc(move_struct->points, numMalloc);
            }
            DijkstraAlgoritm_B(turist, fp_out, turist->passeio.points[i], turist->passeio.points[i + 1], &index, &pontos_atuais, move_struct);
		}
	}
	else
	{
		// write file with failure because one (or more) point(s) aren't inside the matrix
		WriteFileWithFailure(turist, fp_out);
		return;
	}

    free(vect_out);

	// write file with success with the cost of the movement
	//WriteFileWithSuccess(turist, fp_out);
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

//Função encarregue de fazer os movimentos para todos os lados possiveis e ver qual é que é mais barato
/*
 PARAM:
  -> NEW: Matriz com os dados da matriz
*/
void movimentos(Problema *new)
{
    char variavelx = 'x';
    char variavely = 'y';
    new->passeio.custo_total = 10000;

    movimentos_num_ponto(new, getXSize(new->tabu), getYSize(new->tabu), get_X_From_Point(new->passeio.points[0]),
        get_Y_From_Point(new->passeio.points[0]) - 2, variavelx); //move_HIGH

    movimentos_num_ponto(new, getXSize(new->tabu), getYSize(new->tabu), get_X_From_Point(new->passeio.points[0]),
        get_Y_From_Point(new->passeio.points[0]) + 2, variavelx); //move_LOW

    movimentos_num_ponto(new, getXSize(new->tabu), getYSize(new->tabu), get_X_From_Point(new->passeio.points[0]) + 2,
        get_Y_From_Point(new->passeio.points[0]), variavely); //move_low_right

    movimentos_num_ponto(new, getXSize(new->tabu), getYSize(new->tabu), get_X_From_Point(new->passeio.points[0]) - 2,
        get_Y_From_Point(new->passeio.points[0]), variavely); //move_low_left

    if(new->passeio.custo_total == 10000)
        new->passeio.custo_total = 0;
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


//Função que tem como variáveis uma condição,  que pode ser x ou y,  por exemplo,  se for x,  quer dizer que é o x que varia entre 1 ou -1 enquanto a outro váriavel mantêm-se fixa,
// esta função tem por base o facto de que em todos os movimentos existe sempre uma variavel que varia -2 ou +2,  mas mantêm-se,  enquanto a outro varia entre -1 e 1
// PARAM:
/*
    new ->matriz com os dados do ficheiro
    xmax e ymax -> dimensões da matriz
    x e y-> ponto de partida
    condição -> Se a variável que oscila entre 1 e -1 é a x ou y
    soma_min ->  soma mínima das operaçoes
*/
void movimentos_num_ponto(Problema *new, int xmax, int ymax, int x, int y, char condicao)
{
    int soma2 = 0, soma1 = 0;

    if(condicao == 'y')
    {
        if(x < xmax && (y + 1) < ymax && x >= 0)
            soma1 = GetPointCostFromCoord(new->tabu, y + 1, x);

        if(x < xmax && x >= 0 && (y - 1) >= 0)
            soma2 = GetPointCostFromCoord(new->tabu, y - 1, x);

        if( soma1 <= new->passeio.custo_total && soma1 != 0)
            new->passeio.custo_total = soma1;

        if( soma2 <= new->passeio.custo_total && soma2 != 0)
            new->passeio.custo_total = soma2;
    }
    else
    {
        if((x + 1) < xmax && y < ymax && y >= 0)
            soma1 = GetPointCostFromCoord(new->tabu, y, x + 1);

        if( y < ymax && (x - 1) >= 0 && y >= 0)
            soma2 = GetPointCostFromCoord(new->tabu, y, x - 1);

        if( soma1 <= new->passeio.custo_total && soma1 != 0)
            new->passeio.custo_total = soma1;

        if( soma2 <= new->passeio.custo_total && soma2 != 0)
            new->passeio.custo_total = soma2;

    }
}
