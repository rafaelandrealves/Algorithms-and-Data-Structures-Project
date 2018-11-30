

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
 * [get_Acum_Cost description]
 * @param  aux   [description]
 * @param  ponto [description]
 * @return       [description]
 */
int get_Acum_Cost(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].acum_cost;
}


/**
 * [get_Father description]
 * @param  aux   [description]
 * @param  ponto [description]
 * @return       [description]
 */
point * get_Father(DijkMatrix aux, point * ponto)
{
    return aux[get_Y_From_Point(ponto)][get_X_From_Point(ponto)].pai;
}


/**
 * [AllocDijk description]
 * @param  ysize [description]
 * @param  xsize [description]
 * @return       [description]
 */
DijkMatrix AllocDijk(int ysize, int xsize)
{
    DijkMatrix new = (DijkMatrix) Checked_Malloc(sizeof(Dijk *) * ysize);

    for(int i = 0; i < ysize; i++)
        new[i] = (Dijk *) Checked_Malloc(sizeof(Dijk) * xsize);

    return new;
}


/**
 * [FreeDijk description]
 * @param matrix [description]
 * @param ysize  [description]
 * @param xsize  [description]
 */
void FreeDijk(DijkMatrix matrix, int ysize, int xsize)
{
    for(int i = 0; i < ysize; i++)
        free(matrix[i]);

    free(matrix);
}

/**
 * [Problema2Dijk description]
 * @param  turist [description]
 * @return        [description]
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
 * [Possible_Jump_Points description]
 * @param  tab   [description]
 * @param  ponto [description]
 * @param  aux   [description]
 * @return       [description]
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
 * [Free_Possible_Jump_Points description]
 * @param vect [description]
 */
void Free_Possible_Jump_Points(point ** vect)
{
    for(int i = 0; i < 8; i++)
        if(vect[i] != NULL)
            free(vect[i]);
}

/**
 * [Prints the vector of one move]
 * @param matrix [Dijkstra Struct **]
 * @param end    [pointer to the last point of the move]
 * @param ORIGIN [origin point]
 * @param turist [struct with the info read from the file]
 * @param fp_out [pointer to the output file]
 */
void get_Move_Vector(DijkMatrix matrix, point * end, point * ORIGIN, Problema * turist, FILE * fp_out)
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
 * [DijkstraAlgoritm description]
 * @param turist [description]
 * @param argv   [description]
 * @param fp_out [description]
 */
void DijkstraAlgoritm(Problema * turist, char *argv,FILE * fp_out)
{
    DijkMatrix matrix = Problema2Dijk(turist);
    Acervo * heap_tree = InitAcervo();

    point * ORIGIN_POINT = getIpoint(turist, 0);
    point * DESTINY_POINT = getIpoint(turist, 1);

    point * min = ORIGIN_POINT;

    matrix[get_Y_From_Point(ORIGIN_POINT)][get_X_From_Point(ORIGIN_POINT)].acum_cost = 0;

    HeapInsertPoint(matrix,heap_tree,ORIGIN_POINT);

    while( !SamePoint(getIPointFromHeap(heap_tree,0),DESTINY_POINT) && EmptyHeap(heap_tree) != 0)
    {
        min = HeapDeleteMaxPoint( matrix, heap_tree);
        if( get_Acum_Cost(matrix,min) != INF)
        {
            point ** ppoints = Possible_Jump_Points(getTabuleiro(turist),min,matrix);
            for(int i = 0; i < 8; i++)
            {
                if(ppoints[i] != NULL)
                {
                    if(matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost >
                        (matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]) ))
                    {
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].acum_cost =
                            matrix[get_Y_From_Point(min)][get_X_From_Point(min)].acum_cost + GetPointCostFromPoint(getTabuleiro(turist), ppoints[i]);
                        //FixDown(matrix,heap_tree,i,getFree(heap_tree));
                        matrix[get_Y_From_Point(ppoints[i])][get_X_From_Point(ppoints[i])].pai = min;
                        HeapInsertPoint(matrix,heap_tree,ppoints[i]);

                    }
                }
            }
        }

    }
    min = HeapDeleteMaxPoint(matrix, heap_tree);
    get_Move_Vector(matrix,min, ORIGIN_POINT, turist, fp_out);





    // Free_Possible_Jump_Points(pontos);
    // free(pontos);

    FreeDijk(matrix, getYSize(getTabuleiro(turist)), getXSize(getTabuleiro(turist)));
    FreeAcervo(heap_tree);

}
