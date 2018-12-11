
/******************************************************************************
 *
 * File Name: points.c

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  11 Dez 2018
 *
 * NAME
 *     points.c - Functions related to points like set one point, check if it is the same point, ...
 *
*/

#include "defs.h"
#include "util.h"
#include "points.h"

/**
 * Given 2 points checks if are the same point
 * @param  ponto1 [point 1]
 * @param  ponto2 [point 2]
 * @return        [true in case of being the same point]
 */
bool SamePoint(point ponto1, point ponto2)
{
    if( ponto1.x == ponto2.x && ponto1.y == ponto2.y)
        return true;
    else
        return false;
}

/**
 * Given 2 points cheks if it is a horse jump
 * @param  ponto1 [point 1]
 * @param  ponto2 [point 2]
 * @return        [true if it is a horse jump]
 */
bool CheckHorseJump(point ponto1, point ponto2)
{
    if (SamePoint(ponto1, ponto2))
        return false;

    // the point2 is 2 cells above the point1 or the point2 it 2 cells under point1
    if((ponto1.y == (ponto2.y + 2)) || (ponto1.y == (ponto2.y - 2)) )
    {
        // now the point2 only can be 1 cell to the left or 1 cell to the right
        if((ponto1.x == (ponto2.x + 1)) || (ponto1.x == (ponto2.x - 1)) )
            return true;
    }
    // the point2 is 2 cells on the left of point1 or the point2 it 2 cells on the right of point1
    else if((ponto1.x == (ponto2.x + 2)) || (ponto1.x == (ponto2.x - 2)) )
    {
        // now the point2 only can be 1 cell under or 1 cell above the point1
        if((ponto1.y == (ponto2.y + 1)) || (ponto1.y == (ponto2.y - 1)) )
            return true;
    }

    return false;
}

/**
 * [Given one point * it sets the x and y values of that point]
 * @param  ponto [addres of point]
 * @param  x     [x value]
 * @param  y     [y value]
 */
void SetPoint(point * ponto, int x, int y)
{
    ponto->x = x;
    ponto->y = y;
}
