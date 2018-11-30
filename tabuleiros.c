
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
 * Funtion that gets the size of the matrix in terms of columns
 * @param  table [matrix given by the initial problem]
 * @return [Size of the matrix]      
 */
int getXSize(tabuleiro * table)
{
    return table->size_x;
}

/**
 * Funtion that gets the size of the matrix in terms o lines
 * @param  table [matrix given by the initial problem]
 * @return Size of the matrix      
 */
int getYSize(tabuleiro * table)
{
    return table->size_y;
}

/**
 * Function that gets the pointer to a matrix 
 * @param  table [pointer to a struct cointaining the matrix wanted]
 * @return       [pointer to the matrix wanted]
 */
int ** getMatrixPointer(tabuleiro * table)
{
    return table->tab;
}

/**
 * Funciton that gets a pointer to a certain line of the matrix provided
 * @param  table [Matrix containing the line needed]
 * @param  i     [Index of de line wanted]
 * @return       [Pointer to matrix line]
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
 * Function that obtains the point cost from a coordinate given
 * @param  table [Matrix given by the initial file]
 * @param  yy    [Line of the point]
 * @param  xx    [Column of the point]
 * @return       [Point cost of a certain point]
 */
int GetPointCostFromCoord(tabuleiro * table, int yy, int xx)
{
    return (int)(table->tab[yy][xx]);
}

/**
 * [Allocates initial matrix identical to the one given by the initial file]
 * @param  table [Struct pointer to contain the matrix]
 * @param  sizey [Number of lines]
 * @param  sizex [Number of columns]
 * @return       [Pointer to matrix created]
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
 * Establish a certain cost to a position of the matrix
 * @param table [Struct with the matrix with the position to change]
 * @param cost  [Cost to switch]
 * @param yy    [Line]
 * @param xx    [Column]
 */
void SetMatrixElement(tabuleiro * table, int cost, int yy, int xx)
{
    table->tab[yy][xx] = cost;
}
