
/******************************************************************************
 *
 * File Name: leitura_fich.c

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  27 Oct 2018
 *
 * NAME
 *     util.c - Implementation of reading file functions
 *
*/



#include "defs.h"
#include "util.h"
#include "points.h"


struct tabuleiro_t
{
    int size_x; // sizes of the table
    int size_y;
    int ** tab; // table matrix
};

#include "tabuleiros.h"

/**
 * [getXSize description]
 * @param  table [description]
 * @return       [description]
 */
int getXSize(tabuleiro * table)
{
    return table->size_x;
}

/**
 * [getYSize description]
 * @param  table [description]
 * @return       [description]
 */
int getYSize(tabuleiro * table)
{
    return table->size_y;
}

/**
 * [getMatrixPointer description]
 * @param  table [description]
 * @return       [description]
 */
int ** getMatrixPointer(tabuleiro * table)
{
    return table->tab;
}

/**
 * [getMatrixLinePointer description]
 * @param  table [description]
 * @param  i     [description]
 * @return       [description]
 */
int * getMatrixLinePointer(tabuleiro * table, int i)
{
    return table->tab[i];
}

/**
 * [getSizeOfTabuleiro description]
 * @return [description]
 */
size_t getSizeOfTabuleiro()
{
    return sizeof(tabuleiro);
}
/**
 * Checks if one point is inside the table
 * @param  table [city map]
 * @param  ponto [point to check if is inside the table]
 * @return       [returns true is is inside the table]
 */
bool check_Point_Inside_Table(tabuleiro * table, point * ponto)
{
    int x = get_X_From_Point(ponto);
    int y = get_Y_From_Point(ponto);

    if((x < table->size_x) && (x >= 0) && (y < table->size_y) && (y >= 0))
        return true;

    return false;

}

/**
 * Checks if a point is accessable which means that it is inside the matrix and has a cost != 0
 * @param  table [table of problem]
 * @param  ponto [point to be checked]
 * @return       [true if valid]
 */
bool check_Point_Acessibility(tabuleiro * table, point * ponto)
{
    int x = get_X_From_Point(ponto);
    int y = get_Y_From_Point(ponto);

    if((x < table->size_x) && (x >= 0) && (y < table->size_y) && (y >= 0) && (GetPointCostFromCoord(table, y, x) != 0))
        return true;

    return false;
}

/**
 * Returns the cost of one given point
 * @param  table [table matrix]
 * @param  ponto [point to get the cost]
 * @return       [cost of that point]
 */
int GetPointCostFromPoint(tabuleiro * table, point * ponto)
{
    return (int)(table->tab[get_Y_From_Point(ponto)][get_X_From_Point(ponto)]);
}

/**
 * [GetPointCostFromCoord description]
 * @param  table [description]
 * @param  yy    [description]
 * @param  xx    [description]
 * @return       [description]
 */
int GetPointCostFromCoord(tabuleiro * table, int yy, int xx)
{
    return (int)(table->tab[yy][xx]);
}

/**
 * [Set_Lenght_Width description]
 * @param  table [description]
 * @param  sizey [description]
 * @param  sizex [description]
 * @return       [description]
 */
tabuleiro * Set_Lenght_Width(tabuleiro * table, int sizey, int sizex)
{
    table->size_x = sizex;
    table->size_y = sizey;
    table->tab = (int **) Checked_Malloc(sizey * sizeof(int*));
    for(int i = 0; i < sizey; i++)
        table->tab[i] = (int *) Checked_Malloc(sizex * sizeof(int));

    return table;
}

/**
 * [SetMatrixElement description]
 * @param table [description]
 * @param cost  [description]
 * @param yy    [description]
 * @param xx    [description]
 */
void SetMatrixElement(tabuleiro * table, int cost, int yy, int xx)
{
    table->tab[yy][xx] = cost;
}
