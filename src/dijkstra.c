
/******************************************************************************
 *
 * File Name: dijkstra.c

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  11 Dez 2018
 *
 * NAME
 *     dijkstra.c - Functions related to the dijkstra algorith
 *
*/


#include "defs.h"
#include "points.h"
#include "util.h"
#include "tabuleiros.h"
#include "moves.h"
#include "acervo.h"


struct Dijk_struct
{
    short acum_cost;
    point pai;
};

#include "dijkstra.h"

/**
 * Returns the Acumulated cost of a point given
 * @param  aux   [Matrix with acumulated cost and father bond of each point]
 * @param  ponto [point struct to consider]
 * @return       [acumulated cost of point given]
 */
int get_Acum_Cost(DijkMatrix matrix, point ponto)
{
    return matrix[ponto.y][ponto.x].acum_cost;
}


/**
 * Returns the Father point of the point given
 * @param  aux   [Matrix with acumulated cost and father bond of each point]
 * @param  ponto [point struct to consider]
 * @return       [father point]
 */
point get_Father(DijkMatrix matrix, point ponto)
{

    return matrix[ponto.y][ponto.x].pai;
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


/**
 * Free of Matrix with acumulated cost and father bond of each point
 * @param matrix [Matrix with acumulated cost and father bond of each point]
 * @param ysize  [max size of the lines on the matrix given]
 * @param xsize  [max size of the columns on the matrix given]
 */
void FreeDijk(DijkMatrix matrix, int ysize, int xsize)
{
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
            new[i][j].pai = getIpoint(turist, 0);
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
point * Possible_Jump_Points(tabuleiro * tab, point ponto, DijkMatrix aux)
{
    point * new = (point *) Checked_Malloc(sizeof(point) * 8);

    SetPoint(&new[0], ponto.x + 1, ponto.y - 2);
    if(!check_Point_Acessibility(tab, new[0]))
        SetPoint(&new[0], -1, -1);

    SetPoint(&new[1], ponto.x + 2, ponto.y - 1);
    if(!check_Point_Acessibility(tab, new[1]))
        SetPoint(&new[1], -1, -1);

    SetPoint(&new[2], ponto.x + 2, ponto.y + 1);
    if(!check_Point_Acessibility(tab, new[2]))
        SetPoint(&new[2], -1, -1);

    SetPoint(&new[3], ponto.x + 1, ponto.y + 2);
    if(!check_Point_Acessibility(tab, new[3]))
        SetPoint(&new[3], -1, -1);

    SetPoint(&new[4], ponto.x - 1, ponto.y + 2);
    if(!check_Point_Acessibility(tab, new[4]))
        SetPoint(&new[4], -1, -1);

    SetPoint(&new[5], ponto.x - 2, ponto.y + 1);
    if(!check_Point_Acessibility(tab, new[5]))
        SetPoint(&new[5], -1, -1);

    SetPoint(&new[6], ponto.x - 2, ponto.y - 1);
    if(!check_Point_Acessibility(tab, new[6]))
        SetPoint(&new[6], -1, -1);

    SetPoint(&new[7], ponto.x - 1, ponto.y - 2);
    if(!check_Point_Acessibility(tab, new[7]))
        SetPoint(&new[7], -1, -1);

    return new;
}


/**
 * [Funtion that prints the diferent points of the course to the destination on the exit file]
 * @param matrix [matrix with the acumulated cost and father bond of each point]
 * @param end    [Destiny point]
 * @param ORIGIN [Origin point]
 * @param turist [Struct with the matrix given by the initial file]
 * @param fp_out [File to insert the output]
 */
void get_Move_Vector_A(DijkMatrix matrix, point end, point ORIGIN, Problema * turist, FILE * fp_out)
{
    int num = 0;
    point min = end;

    // to get the number of points in the path
    for(num = 0; !SamePoint(min, ORIGIN); num++)
    {
        min = get_Father(matrix, min);
    }

    // alloc a vector with the size of number of points that the path need
    point * vect = (point *) Checked_Malloc(num * sizeof(point));

    min = end;
    for(int i = 0; i < num; i++)
    {
        vect[num - i - 1] = min;
        min = get_Father(matrix, min);
    }
    fprintf(fp_out, "%d %d %c %d %d %d\n", getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)), GetModoJogo(turist), getNumPontos(turist), get_Acum_Cost(matrix,end), num);
    for (int i = 0 ; i < num; i++)
    {
        fprintf(fp_out,"%d %d %d \n", vect[i].y, vect[i].x, GetPointCostFromPoint(getTabuleiro(turist), vect[i]));
    }
    fprintf(fp_out,"\n");
    free(vect);
}


/**
 * [Sets the vect point vector with the points of the path]
 * @param matrix [matrix with the acumulated cost and father bond of each point]
 * @param end    [Destiny point]
 * @param ORIGIN [Origin point]
 * @param num_pontos  [number of points]
 * @param vect   [point vector to insert the path]
 */
void get_Move_Vector_B(DijkMatrix matrix, point end, point ORIGIN, int *num_pontos, point * vect)
{
    int num = 0;
    point min = end;

    // to get the number of points to tha path
    for(num = 0; !SamePoint(min, ORIGIN); num++, min = get_Father(matrix, min));

    min = end;
    // printf("O num + index =%d\n",num + *index);
    for(int i = 0; i < num; i++)
    {
        vect[(num + *num_pontos) - i - 1] = min;
        min = get_Father(matrix, min);
    }

    *num_pontos = num + *num_pontos;
}

/**
 * [OutPUT_B description]
 * @param turist     [Problem read from file]
 * @param fp_out     [file pointer to the output file]
 * @param num_pontos [number of points in the vector]
 * @param atual      [path with the points]
 */
void OutPUT_B(Problema * turist, FILE * fp_out, int num_pontos, caminho * atual)
{
    fprintf(fp_out, "%d %d %c %d %d %d\n", getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)), GetModoJogo(turist), getNumPontos(turist),
        getCustoTotalFromCaminho(atual), num_pontos);
    for (int i = 0 ; i < num_pontos; i++)
    {
        fprintf(fp_out,"%d %d %d \n", getIpointFromCaminho(atual, i).y, getIpointFromCaminho(atual, i).x,
                    GetPointCostFromPoint(getTabuleiro(turist), getIpointFromCaminho(atual, i)));
    }
    fprintf(fp_out,"\n");

}

/**
 * [Given 2 points is calculates the cheapest path from 'begin' to 'end']
 * @param turist [problem read from file]
 * @param fp_out [file pointer to the output file]
 * @param begin  [begin point of the path]
 * @param end    [end point of the path]
 */
void DijkstraAlgoritm_A(Problema * turist,FILE * fp_out, point begin, point end)
{
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo(getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));

    point ORIGIN_POINT = begin;
    point DESTINY_POINT = end;

    point min = ORIGIN_POINT;

    matrix[ORIGIN_POINT.y][ORIGIN_POINT.x].acum_cost = 0;

    HeapInsertPoint(matrix, heap_tree, min);

    while( EmptyHeap(heap_tree) != 0 &&  !SamePoint(getIPointFromHeap(heap_tree, 0), DESTINY_POINT))
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);

        point * ppoints = Possible_Jump_Points(getTabuleiro(turist), min, matrix);
        for(int i = 0; i < 8; i++)
        {
            // invalid point
            if(ppoints[i].x == -1 && ppoints[i].y == -1)
                continue;

            // the point had never been in the heap
            if(get_Idx_matrix(heap_tree, ppoints[i]) == -1)
            {

                point aux1 = ppoints[i];
                matrix[ppoints[i].y][ppoints[i].x].acum_cost = matrix[min.y][min.x].acum_cost +
                    GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);
                matrix[ppoints[i].y][ppoints[i].x].pai = min;
                HeapInsertPoint(matrix, heap_tree, aux1);
            }
            // the point was in the heap and it was already deleted
            else if(get_Idx_matrix(heap_tree, ppoints[i]) == -2)
            {
                continue;
            }
            // if is finds a better jump to optimise the path
            else if( matrix[ppoints[i].y][ppoints[i].x].acum_cost >
            (matrix[min.y][min.x].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i])) )
            {
                matrix[ppoints[i].y][ppoints[i].x].acum_cost =
                    matrix[min.y][min.x].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);

                // fixup from the point to keep the heap order by priority
                FixUp(matrix, heap_tree, get_Idx_matrix(heap_tree, ppoints[i]));
            }
        }
        free(ppoints);
    }

    // when the dijkstra finished means that there is no possible path or the next point to remove from heap is the destiny point
    if(EmptyHeap(heap_tree) == 0)
    {
        WriteFileWithFailure(turist, fp_out);
    }
    else
    {
        min = HeapDeleteMaxPoint(matrix, heap_tree);
        get_Move_Vector_A(matrix, min, ORIGIN_POINT, turist, fp_out);
    }

    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree, getYSize(getTabuleiro(turist)));

}


/**
 * [Gets the cheapest path from 'begin' to 'end' ]
 * @param turist [problem read from file]
 * @param fp_out [file pointer to the output file]
 * @param begin  [begin point of the path]
 * @param end    [end point of the path]
 * @param num_pontos [number of points]
 * @param ponto_atual [number of the actual points to see when the dijkstra is ready]
 * @param atual       [actual move]
 */
void DijkstraAlgoritm_B(Problema * turist, FILE * fp_out, point begin, point end, int *num_pontos, int *ponto_atual, caminho * atual)
{
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo(getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    bool validity_origin = false,validity_destiny=false ;

    point ORIGIN_POINT = begin;
    point DESTINY_POINT = end;

    point min = ORIGIN_POINT;

    matrix[ORIGIN_POINT.y][ORIGIN_POINT.x].acum_cost = 0;

    // verifies if either the originpoint or the destination point have a possible jump
    point * to_verify_origin = Possible_Jump_Points(getTabuleiro(turist), ORIGIN_POINT, matrix);
    point * to_verify_destiny = Possible_Jump_Points(getTabuleiro(turist), DESTINY_POINT, matrix);
    for(int i = 0; i < 8; i = i + 1)
    {
        if(!(to_verify_origin[i].x == -1 || to_verify_origin[i].y == -1 ))
        {
            validity_origin = true;
        }
        if(!(to_verify_destiny[i].x == -1 || to_verify_destiny[i].y == -1))
        {
            validity_destiny = true;
        }
    }

    free(to_verify_origin);
    free(to_verify_destiny);

    HeapInsertPoint(matrix, heap_tree, min);

    while( validity_origin == true && validity_destiny == true && EmptyHeap(heap_tree) != 0 && !SamePoint(getIPointFromHeap(heap_tree, 0), DESTINY_POINT))
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);

        point * ppoints = Possible_Jump_Points(getTabuleiro(turist), min, matrix);
        for(int i = 0; i < 8; i++)
        {
            if(ppoints[i].x == -1 && ppoints[i].y == -1) // invalid point
                continue;

            // the point had never been in the heap
            if(get_Idx_matrix(heap_tree, ppoints[i]) == -1)
            {
                point aux1 = ppoints[i];

                matrix[ppoints[i].y][ppoints[i].x].acum_cost = matrix[min.y][min.x].acum_cost +
                    GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);
                matrix[ppoints[i].y][ppoints[i].x].pai = min;
                // insert the point in the heap
                HeapInsertPoint(matrix, heap_tree, aux1);
            }
            // the point was in the heap and it was already deleted from it
            else if(get_Idx_matrix(heap_tree, ppoints[i]) == -2)
            {
                continue;
            }
            // the point is in the heap and there there is a better way to reach it
            else if( matrix[ppoints[i].y][ppoints[i].x].acum_cost >
            (matrix[min.y][min.x].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i])) )
            {
                matrix[ppoints[i].y][ppoints[i].x].acum_cost =
                    matrix[min.y][min.x].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);

                FixUp(matrix, heap_tree, get_Idx_matrix(heap_tree, ppoints[i]));
            }
        }
        free(ppoints);
    }

    // there is no way to reach the final point
    if(EmptyHeap(heap_tree) == 0 || !(validity_origin && validity_destiny))
    {
        WriteFileWithFailure(turist, fp_out);
    }
    else
    {
        min = HeapDeleteMaxPoint(matrix, heap_tree);
        atual = Set_Custo_Total(atual, getCustoTotalFromCaminho(atual) + get_Acum_Cost(matrix, min));
        get_Move_Vector_B(matrix, min, ORIGIN_POINT, num_pontos, get_point_vector(atual));
        *ponto_atual = *ponto_atual + 1;
        // when there are no more points to see is writes the file
        if(*ponto_atual == getNumPontos(turist) - 1)
        {
            OutPUT_B(turist, fp_out, *num_pontos, atual);
        }
    }

    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree, getYSize(getTabuleiro(turist)));
}

/**
 * [get the path points for one step_ path]
 * @param  matrix       [DIjkstra Matrix]
 * @param  end          [destination point]
 * @param  ORIGIN       [origin point]
 * @param  for_one_step [point vector for one path]
 * @return              [number of points]
 */
 int get_Move_Vector_C(DijkMatrix matrix, point end, point ORIGIN, point * for_one_step)
{
    int num = 0;
    point min = end;

    // to calculate the number of points
    for(num = 0; !SamePoint(min, ORIGIN); num++, min = get_Father(matrix, min));

    min = end;
   // printf("olaa %d\n",num);
    for(int i = 0; i < num; i++)
    {
        // printf("olaa1\n");
        //atual[(num + *num_total_pontos) - i - 1] = min;
        for_one_step[num - i - 1] = min;
        min = get_Father(matrix, min);
    }
    //*num_total_pontos = num + *num_total_pontos;
    return num;
}


/**
 * [Calculates the cheapest move from 'begin' to 'end']
 * @param turist        [problem read from the file]
 * @param begin         [inicial point]
 * @param end           [end point]
 * @param momentum      [move for one step]
 * @param number_points [number of points in that move]
 * @param No_Path       [variable to set == true if there is no path]
 */
void DijkstraAlgoritm_C(Problema * turist, point begin, point end, caminho *momentum, int *number_points, bool * No_Path)
{
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo(getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    bool validity_origin = false, validity_destiny = false;

    point ORIGIN_POINT = begin;
    point DESTINY_POINT = end;

    point min = ORIGIN_POINT;

    // verifies if either the originpoint or the destination point have a possible jump
    point * to_verify_origin = Possible_Jump_Points(getTabuleiro(turist), ORIGIN_POINT, matrix);
    point * to_verify_destiny = Possible_Jump_Points(getTabuleiro(turist), DESTINY_POINT, matrix);
    for(int i = 0; i < 8; i = i + 1)
    {
        if(!(to_verify_origin[i].x == -1 || to_verify_origin[i].y == -1 ))
        {
            validity_origin = true;
        }
        if(!(to_verify_destiny[i].x == -1 || to_verify_destiny[i].y == -1))
        {
            validity_destiny = true;
        }
    }

    free(to_verify_origin);
    free(to_verify_destiny);

    matrix[ORIGIN_POINT.y][ORIGIN_POINT.x].acum_cost = 0;


    HeapInsertPoint(matrix, heap_tree, min);

    while( validity_origin == true && validity_destiny == true && EmptyHeap(heap_tree) != 0 && !SamePoint(getIPointFromHeap(heap_tree, 0), DESTINY_POINT) )
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);
        point * ppoints = Possible_Jump_Points(getTabuleiro(turist), min, matrix);

        for(int i = 0; i < 8; i++)
        {
            if(ppoints[i].x == -1 && ppoints[i].y == -1) // invalid point
            {
                continue;
            }

            // the point had never been in the heap so it will be inserted
            if(get_Idx_matrix(heap_tree, ppoints[i]) == -1)
            {

                point aux1 = ppoints[i];

                matrix[ppoints[i].y][ppoints[i].x].acum_cost = matrix[min.y][min.x].acum_cost +
                    GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);
                matrix[ppoints[i].y][ppoints[i].x].pai = min;
                HeapInsertPoint(matrix, heap_tree, aux1);
            }
            // the point was in the heap but was already deleted
            else if(get_Idx_matrix(heap_tree, ppoints[i]) == -2)
            {
                continue;
            }
            // the point is in the heap and was found one cheapest path so the cost will be replaced
            else if( matrix[ppoints[i].y][ppoints[i].x].acum_cost >
            (matrix[min.y][min.x].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i])) )
            {
                matrix[ppoints[i].y][ppoints[i].x].acum_cost =
                    matrix[min.y][min.x].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);

                FixUp(matrix, heap_tree, get_Idx_matrix(heap_tree, ppoints[i]));
            }
        }
        free(ppoints);
    }

    // there is no possible move or either the origin point or destiny point have no jump possibilities
    if(EmptyHeap(heap_tree) == 0 || !(validity_origin && validity_destiny))
    {
        *No_Path = true;
    }
    else
    {
        min = HeapDeleteMaxPoint(matrix, heap_tree);
        momentum = Set_Custo_Total(momentum, get_Acum_Cost(matrix, min));
        *number_points = get_Move_Vector_C(matrix, min, ORIGIN_POINT, get_point_vector(momentum));
        //printf("num_pts_1combin-%d --- custo--%d-- ponto_atual %d--pontos %d\n",*num_pts_1combin,*custo_total_acumulado,*ponto_atual,num_pontos);
    }


    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree, getYSize(getTabuleiro(turist)));
}


/**
 * [printf the soluction file to variant C problem]
 * @param turist [problem read from file]
 * @param fp_out [file pointer to the output file]
 * @param best   [vector of move pointers]
 */
void OutPUT_C(Problema * turist, FILE * fp_out, caminho ** best)
{
    int custo_total = 0,numero_de_pontos = 0;

    for(int i = 0; i < (getNumPontos(turist)- 1) && best[i] != NULL; i++)
    {
        custo_total += getCustoTotalFromCaminho(best[i]);
        numero_de_pontos += getNumPontosFromCaminho(best[i]);
    }

    fprintf(fp_out, "%d %d %c %d %d %d\n", getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)), GetModoJogo(turist), getNumPontos(turist),
        custo_total, numero_de_pontos);
    //printf("olaaa\n");

    for (int i = 0 ; i < getNumPontos(turist) - 1; i++)
    {
        for(int j = 0; j < getNumPontosFromCaminho(best[i]); j++)
        {
            fprintf(fp_out,"%d %d %d\n", getIpointFromCaminho(best[i], j).y, getIpointFromCaminho(best[i], j).x,
                GetPointCostFromPoint(getTabuleiro(turist), getIpointFromCaminho(best[i], j)));


        }
        //printf("olaaa\n");

        //printf("%d %d \n",get_Y_From_Point(getIpointFromCaminho(atual, i)), get_X_From_Point(getIpointFromCaminho(atual, i)));
    }
    fprintf(fp_out,"\n");

}
