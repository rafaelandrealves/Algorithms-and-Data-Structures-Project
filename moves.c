


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "dijkstra.h"


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
int getCustoTotal(Problema * turist)
{
	return getCaminho(turist)->custo_total;
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
    int custo_total_acumulado = 0;
    int pontos_atuais = 0;
    point ** vect_out =(point **) Checked_Malloc(300 * sizeof(point *));
    

	// means that one or more points aren't inside the table or are inaccessible
	validity = CheckAllPoints(turist);

	if(validity == true) // if all points are valid program will check if all make horse jumps
	{
		for(int i = 0; i < turist->passeio.num_pontos - 1; i++)
		{
            DijkstraAlgoritm(turist,fp_out,turist->passeio.points[i],turist->passeio.points[i+1],&custo_total_acumulado,&index,&pontos_atuais,vect_out, turist->passeio.num_pontos);
		}
	}
	else
	{
		// write file with failure because one (or more) point(s) aren't inside the matrix or are
		WriteFileWithFailure(turist, fp_out);
		return;
	}

	// write file with success with the cost of the movement
	//WriteFileWithSuccess(turist, fp_out);
}

/**
 * Given one point it gets the cheapest point to reach with just one move
 * @param turist [main struct]
 * @param fp_out [output file pointer to]
 */
void Execute_A_Variant(Problema * turist, FILE * fp_out, char *argv)
{
 	bool sign = false;
	sign = CheckAllPoints(turist);
    int index = 0;
    int custo_total_acumulado = 0;
    int pontos_atuais = 0;
    point ** vect_out = (point **)Checked_Malloc(sizeof(point*));

	if(sign == false)
		WriteFileWithFailure(turist, fp_out);
	else
	{
        DijkstraAlgoritm(turist,fp_out,turist->passeio.points[0],turist->passeio.points[1],&custo_total_acumulado,&index,&pontos_atuais,vect_out,turist->passeio.num_pontos);
        // movimentos(turist);
		// if(turist->passeio.custo_total != 0)
		// 	WriteFileWithSuccess(turist, fp_out);
		// else
		// 	WriteFileWithFailure(turist, fp_out);
        //
		// sign = false;

	}
}

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
    fprintf(fp_out, "%d %d %c %d 1 %d\n\n", getYSize(turist->tabu), getXSize(turist->tabu), GetModoJogo(turist), getNumPontos(turist), getCustoTotal(turist));
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
