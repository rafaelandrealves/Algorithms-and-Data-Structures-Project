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
    short ** tab; // table matrix
};

#include "tabuleiros.h"

int getXSize(tabuleiro * table)
{
    return table->size_x;
}

int getYSize(tabuleiro * table)
{
    return table->size_y;
}

short ** getMatrixPointer(tabuleiro * table)
{
    return table->tab;
}

short * getMatrixLinePointer(tabuleiro * table, int i)
{
    return table->tab[i];
}

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
 * Returns the cost of one given point
 * @param  table [table matrix]
 * @param  ponto [point to get the cost]
 * @return       [cost of that point]
 */
int GetPointCostFromPoint(tabuleiro * table, point * ponto)
{
    return (int)(table->tab[get_Y_From_Point(ponto)][get_X_From_Point(ponto)]);
}

int GetPointCostFromCoord(tabuleiro * table, int yy, int xx)
{
    return (int)(table->tab[yy][xx]);
}


tabuleiro * Set_Lenght_Width(tabuleiro * table, int sizey, int sizex)
{
    table->size_x = sizex;
    table->size_y = sizey;
    table->tab = (short **) Checked_Malloc(sizey * sizeof(short*));
    for(int i = 0; i < sizey; i++)
        table->tab[i] = (short *) Checked_Malloc(sizex * sizeof(short));

    return table;
}

void SetMatrixElement(tabuleiro * table, short cost, int yy, int xx)
{
    table->tab[yy][xx] = cost;
}
