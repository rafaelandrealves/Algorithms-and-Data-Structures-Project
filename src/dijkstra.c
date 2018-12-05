

#include "defs.h"
#include "points.h"
#include "util.h"
#include "tabuleiros.h"
#include "moves.h"
#include "acervo.h"


struct Dijk_struct
{
    int acum_cost;
    point * pai;
};

#include "dijkstra.h"

/**
 * Returns the Acumulated cost of a point given
 * @param  aux   [Matrix with acumulated cost and father bond of each point]
 * @param  ponto [point struct to consider]
 * @return       [acumulated cost of point given]
 */
int get_Acum_Cost(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].acum_cost;
}


/**
 * Returns the Father point of the point given
 * @param  aux   [Matrix with acumulated cost and father bond of each point]
 * @param  ponto [point struct to consider]
 * @return       [father point]
 */
point * get_Father(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].pai;
}


/**
 * Allocs a matrix Matrix with acumulated cost and father bond of each point
 * @param  ysize [max size of the lines on the matrix given]
 * @param  xsize [max size of the columns on the matrix given]
 * @return       [matrix allocated]
 */
DijkMatrix AllocDijk(int ysize, int xsize)
{
    DijkMatrix new = (DijkMatrix) Checked_Malloc(sizeof(Dijk *) * ysize);

    for(int i = 0; i < ysize; i++)
    {
        new[i] = (Dijk *) Checked_Malloc(sizeof(Dijk) * xsize);
    }
    return new;
}

point * GetDupPoint(point * ponto)
{
    point * aux = (point *) Checked_Malloc(sizeof(point *));
    aux = SetPoint(aux, get_X_From_Point(ponto), get_Y_From_Point(ponto));
    return aux;
}

/**
 * Free of Matrix with acumulated cost and father bond of each point
 * @param matrix [Matrix with acumulated cost and father bond of each point]
 * @param ysize  [max size of the lines on the matrix given]
 * @param xsize  [max size of the columns on the matrix given]
 */
void FreeDijk(DijkMatrix matrix, int ysize, int xsize)
{
    for(int i = 0; i < ysize; i++)
    {
        for(int j = 0; j < xsize; j++)
        {
            if(matrix[i][j].pai != NULL)
                free(matrix[i][j].pai);
        }
    }

    for(int i = 0; i < ysize; i++)
        free(matrix[i]);

    free(matrix);
}

/**
 * Initializes Matrix for Dijk Algorithm, used for the consecutive acumulated cost and and bond to the father point
 * @param  turist [Struct that has the initial matrix given by the file]
 * @return        [Matrix Initialized with Infinite acumulated cost(for it to be changed in the algorithm) and the ponits linked to the Origin point]
 */
DijkMatrix Problema2Dijk(Problema * turist)
{
    tabuleiro * tab = getTabuleiro(turist);

    DijkMatrix new = AllocDijk(getYSize(tab), getXSize(tab));

    for(int i = 0; i < getYSize(tab); i++)
    {
        for(int j = 0; j < getXSize(tab); j++)
        {
            new[i][j].acum_cost = INF;
            // new[i][j].pai = GetDupPoint(getIpoint(turist, 0));
            new[i][j].pai = NULL;
        }
    }

    return new;
}

/**
 * Function that calculates all the possible horse jump points
 * @param  tab   [Map given by the file]
 * @param  ponto [Point to check the horse jumps]
 * @param  aux   [Matrix whith the acumulated cost and father bond of each point]
 * @return vector whith pointers to each possible jump points
 */
point ** Possible_Jump_Points(tabuleiro * tab, point * ponto, DijkMatrix aux)
{
    point ** new = (point **) Checked_Malloc(sizeof(point *) * 8);

    point * aux0 = (point *) Checked_Malloc(getSizeOfPoint());
    aux0 = SetPoint(aux0, get_X_From_Point(ponto) + 1, get_Y_From_Point(ponto) - 2);
    if(check_Point_Acessibility(tab, aux0))
        new[0] = aux0;
    else
    {
        new[0] = NULL;
        free(aux0);
    }

    point * aux1 = (point *) Checked_Malloc(getSizeOfPoint());
    aux1 = SetPoint(aux1, get_X_From_Point(ponto) + 2, get_Y_From_Point(ponto) - 1);
    if(check_Point_Acessibility(tab, aux1))
        new[1] = aux1;
    else
    {
        new[1] = NULL;
        free(aux1);
    }


    point * aux2 = (point *) Checked_Malloc(getSizeOfPoint());
    aux2 = SetPoint(aux2, get_X_From_Point(ponto) + 2, get_Y_From_Point(ponto) + 1);
    if(check_Point_Acessibility(tab, aux2))
        new[2] = aux2;
    else
    {
        new[2] = NULL;
        free(aux2);
    }


    point * aux3 = (point *) Checked_Malloc(getSizeOfPoint());
    aux3 = SetPoint(aux3, get_X_From_Point(ponto) + 1, get_Y_From_Point(ponto) + 2);
    if(check_Point_Acessibility(tab, aux3))
        new[3] = aux3;
    else
    {
        new[3] = NULL;
        free(aux3);
    }


    point * aux4 = (point *) Checked_Malloc(getSizeOfPoint());
    aux4 = SetPoint(aux4, get_X_From_Point(ponto) - 1, get_Y_From_Point(ponto) + 2);
    if(check_Point_Acessibility(tab, aux4))
        new[4] = aux4;
    else
    {
        new[4] = NULL;
        free(aux4);
    }

    point * aux5 = (point *) Checked_Malloc(getSizeOfPoint());
    aux5 = SetPoint(aux5, get_X_From_Point(ponto) - 2, get_Y_From_Point(ponto) + 1);
    if(check_Point_Acessibility(tab, aux5))
        new[5] = aux5;
    else
    {
        new[5] = NULL;
        free(aux5);
    }

    point * aux6 = (point *) Checked_Malloc(getSizeOfPoint());
    aux6 = SetPoint(aux6, get_X_From_Point(ponto) - 2, get_Y_From_Point(ponto) - 1);
    if(check_Point_Acessibility(tab, aux6))
        new[6] = aux6;
    else
    {
        new[6] = NULL;
        free(aux6);
    }

    point * aux7 = (point *) Checked_Malloc(getSizeOfPoint());
    aux7 = SetPoint(aux7, get_X_From_Point(ponto) - 1, get_Y_From_Point(ponto) - 2);
    if(check_Point_Acessibility(tab, aux7))
        new[7] = aux7;
    else
    {
        new[7] = NULL;
        free(aux7);
    }

    return new;
}

/**
 * Function that frees the vector with jump point
 * @param vect [vector with pointers to points to possibly jump]
 */
void Free_Possible_Jump_Points(point ** vect)
{
    for(int i = 0; i < 8; i++)
        if(vect[i] != NULL)
            free(vect[i]);

    free(vect);
}

/**
 * [Funtion that prints the diferent points of the course to the destination on the exit file]
 * @param matrix [matrix with the acumulated cost and father bond of each point]
 * @param end    [Destiny point]
 * @param ORIGIN [Origin point]
 * @param turist [Struct with the matrix given by the initial file]
 * @param fp_out [File to insert the output]
 */
void get_Move_Vector_A(DijkMatrix matrix, point * end, point * ORIGIN, Problema * turist, FILE * fp_out)
{
    int num = 0;
    point * min = end;

    for(num = 0; !SamePoint(min, ORIGIN); num++, min = get_Father(matrix, min));

    point ** vect = (point **) Checked_Malloc(num * sizeof(point *));

    min = end;
    for(int i = 0; i < num; i++)
    {
        vect[num - i - 1] = min;
        min = get_Father(matrix, min);
    }
    fprintf(fp_out, "%d %d %c %d %d %d\n", getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)), GetModoJogo(turist), getNumPontos(turist), get_Acum_Cost(matrix,end),num);
    for (int i = 0 ; i < num; i++)
    {
        fprintf(fp_out,"%d %d %d \n", get_Y_From_Point(vect[i]), get_X_From_Point(vect[i]), GetPointCostFromPoint(getTabuleiro(turist), vect[i]));
    }
    fprintf(fp_out,"\n");
    free(vect);
}

/**
 * [Funtion that prints the diferent points of the course to the destination on the exit file]
 * @param matrix [matrix with the acumulated cost and father bond of each point]
 * @param end    [Destiny point]
 * @param ORIGIN [Origin point]
 * @param turist [Struct with the matrix given by the initial file]
 * @param fp_out [File to insert the output]
 */
void get_Move_Vector_B(DijkMatrix matrix, point * end, point * ORIGIN, int *index, point ** vect)
{
    int num = 0;
    point * min = end;

    for(num = 0; !SamePoint(min, ORIGIN); num++, min = get_Father(matrix, min));

    min = end;
    //printf("O index é %d e o num %d \n",*index,num);
    for(int i = 0; i < num; i++)
    {
        vect[(num + *index) - i - 1] = GetDupPoint(min);
        min = get_Father(matrix, min);
        //printf("%d %d on pos- %d \n",get_Y_From_Point(vect[(num + * index) - i -1]), get_X_From_Point(vect[(num + *index) - i - 1]),((num + *index) - i -1));
    }

    *index = num + *index;
}


void OutPUT_B(DijkMatrix matrix, point * end, point * ORIGIN, Problema * turist, FILE * fp_out, int num, caminho * move_struct)
{
    fprintf(fp_out, "%d %d %c %d %d %d\n", getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)), GetModoJogo(turist), getNumPontos(turist),
        getCustoTotalFromCaminho(move_struct), num);
    //printf("olaaa\n");
    for (int i = 0 ; i < num; i++)
    {
        fprintf(fp_out,"%d %d %d \n", get_Y_From_Point(getIpointFromCaminho(move_struct, i)), get_X_From_Point(getIpointFromCaminho(move_struct, i)),
                    GetPointCostFromPoint(getTabuleiro(turist), getIpointFromCaminho(move_struct, i)));
        //printf("%d %d \n",get_Y_From_Point(getIpointFromCaminho(move_struct, i)), get_X_From_Point(getIpointFromCaminho(move_struct, i)));
    }
    fprintf(fp_out,"\n");

}

void DijkstraAlgoritm_A(Problema * turist,FILE * fp_out, point * begin, point *end)
{
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo();

    point *ORIGIN_POINT = begin;
    point *DESTINY_POINT = end;

    point * min = GetDupPoint(ORIGIN_POINT);

    matrix[get_Y_From_Point(ORIGIN_POINT)][get_X_From_Point(ORIGIN_POINT)].acum_cost = 0;

    HeapInsertPoint(matrix, heap_tree, min);

    while(  EmptyHeap(heap_tree) != 0 &&  !SamePoint(getIPointFromHeap(heap_tree, 0), DESTINY_POINT))
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);
        if( get_Acum_Cost(matrix, min) != INF)
        {
            point ** ppoints = Possible_Jump_Points(getTabuleiro(turist), min, matrix);
            for(int i = 0; i < 8; i++)
            {
                if(ppoints[i] != NULL)
                {
                    if(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost >
                        (matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]) ))
                    {
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost =
                            matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);

                        // set the father point
                        free(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai);
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai = GetDupPoint(min);

                        // insert the point in the heap
                        point * aux1 = GetDupPoint(ppoints[i]);
                        HeapInsertPoint(matrix, heap_tree, aux1);
                    }
                }
            }
            Free_Possible_Jump_Points(ppoints);
        }
        free(min);
        min = NULL;
    }

    if(EmptyHeap(heap_tree) == 0)
    {
        WriteFileWithFailure(turist, fp_out);
    }
    else
    {
        min = HeapDeleteMaxPoint(matrix, heap_tree);
        get_Move_Vector_A(matrix, min, ORIGIN_POINT, turist, fp_out);
        free(min);
    }

    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree);

}


/**
 * [Funtion that performs the DijkstraAlgorithm in order to find the cheapest course to a Destiny Point]
 * @param turist [Struct that has the initial matrix given by the problem]
 * @param argv   [Pointer to the name of the file]
 * @param fp_out [Exit file to insert the data]
 */
void DijkstraAlgoritm_B(Problema * turist,FILE * fp_out, point * begin, point *end, int *index, int *ponto_atual, caminho * move_struct)
{
    int num_pontos = getNumPontos(turist);
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo();

    point *ORIGIN_POINT = begin;
    point *DESTINY_POINT = end;

    point * min = GetDupPoint(ORIGIN_POINT);

    matrix[get_Y_From_Point(ORIGIN_POINT)][get_X_From_Point(ORIGIN_POINT)].acum_cost = 0;

    HeapInsertPoint(matrix, heap_tree, min);

    while( EmptyHeap(heap_tree) != 0 && !SamePoint(getIPointFromHeap(heap_tree, 0), DESTINY_POINT) )
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);
        if( get_Acum_Cost(matrix, min) != INF)
        {
            point ** ppoints = Possible_Jump_Points(getTabuleiro(turist), min, matrix);
            for(int i = 0; i < 8; i++)
            {
                if(ppoints[i] != NULL)
                {
                    if(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost >
                        (matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]) ))
                    {
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost =
                            matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);

                        // set the father point
                        free(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai);
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai = GetDupPoint(min);

                        // insert the point in the heap
                        point * aux1 = GetDupPoint(ppoints[i]);
                        HeapInsertPoint(matrix, heap_tree, aux1);
                    }
                }
            }
            Free_Possible_Jump_Points(ppoints);
        }
        free(min);
        min = NULL;
    }


    if(EmptyHeap(heap_tree) == 0)
    {
        WriteFileWithFailure(turist, fp_out);
    }
    else
    {
        min = HeapDeleteMaxPoint(matrix, heap_tree);
        move_struct = Set_Custo_Total(move_struct, getCustoTotalFromCaminho(move_struct) + get_Acum_Cost(matrix, min));
        // *custo_total_acumulado = *custo_total_acumulado + get_Acum_Cost(matrix,min);
        get_Move_Vector_B(matrix, min, ORIGIN_POINT, index, get_point_vector(move_struct));
        *ponto_atual = *ponto_atual + 1;
        if(*ponto_atual == num_pontos - 1)
        {
            // OutPUT_B(matrix,min,ORIGIN_POINT, turist, fp_out, *index, vect_out, getCustoTotalFromCaminho(move_struct));
            OutPUT_B(matrix, min, ORIGIN_POINT, turist, fp_out, *index, move_struct);
        }
        //printf("Index-%d --- custo--%d-- ponto_atual %d--pontos %d\n",*index,*custo_total_acumulado,*ponto_atual,num_pontos);
        free(min);

    }

    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree);
}



void DijkstraAlgoritm_C(Problema * turist,FILE * fp_out, point * begin, point *end, caminho * move_struct, int *index)
{
    //int num_pontos = getNumPontos(turist);
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo();

    point *ORIGIN_POINT = begin;
    point *DESTINY_POINT = end;

    point * min = GetDupPoint(ORIGIN_POINT);

    matrix[get_Y_From_Point(ORIGIN_POINT)][get_X_From_Point(ORIGIN_POINT)].acum_cost = 0;

    HeapInsertPoint(matrix, heap_tree, min);

    while( EmptyHeap(heap_tree) != 0 && !SamePoint(getIPointFromHeap(heap_tree, 0), DESTINY_POINT) )
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);

        if( get_Acum_Cost(matrix, min) != INF)
        {
            point ** ppoints = Possible_Jump_Points(getTabuleiro(turist), min, matrix);
            for(int i = 0; i < 8; i++)
            {
                if(ppoints[i] != NULL)
                {
                    if(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost >
                        (matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]) ))
                    {
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost =
                            matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);

                        // set the father point
                        free(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai);
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai = GetDupPoint(min);

                        // insert the point in the heap
                        point * aux1 = GetDupPoint(ppoints[i]);
                        HeapInsertPoint(matrix, heap_tree, aux1);
                    }
                }
            }
            Free_Possible_Jump_Points(ppoints);
        }
        free(min);
        min = NULL;
    }
    if(EmptyHeap(heap_tree) == 0)
    {
        WriteFileWithFailure(turist, fp_out);
    }
    else
    {
        min = HeapDeleteMaxPoint(matrix, heap_tree);
        move_struct = Set_Custo_Total(move_struct, getCustoTotalFromCaminho(move_struct) + get_Acum_Cost(matrix, min));
        // *custo_total_acumulado = *custo_total_acumulado + get_Acum_Cost(matrix,min);
        get_Move_Vector_B(matrix, min, ORIGIN_POINT, index, get_point_vector(move_struct));
        //printf("Index-%d --- custo--%d-- ponto_atual %d--pontos %d\n",*index,*custo_total_acumulado,*ponto_atual,num_pontos);
        free(min);

    }


    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree);

}


void OutPUT_C(point * end, point * ORIGIN, Problema * turist, FILE * fp_out, int num, caminho * move_struct)
{
    fprintf(fp_out, "%d %d %c %d %d %d\n", getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)), GetModoJogo(turist), getNumPontos(turist),
        getCustoTotalFromCaminho(move_struct), num);
    //printf("olaaa\n");
    for (int i = 0 ; i < num; i++)
    {
        fprintf(fp_out,"%d %d %d \n", get_Y_From_Point(getIpointFromCaminho(move_struct, i)), get_X_From_Point(getIpointFromCaminho(move_struct, i)),
                    GetPointCostFromPoint(getTabuleiro(turist), getIpointFromCaminho(move_struct, i)));
        //printf("%d %d \n",get_Y_From_Point(getIpointFromCaminho(move_struct, i)), get_X_From_Point(getIpointFromCaminho(move_struct, i)));
    }
    fprintf(fp_out,"\n");
}
