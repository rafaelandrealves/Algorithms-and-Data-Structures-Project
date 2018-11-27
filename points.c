

#include "defs.h"

struct point_t
{
    int x;
    int y;
};

#include "util.h"
#include "points.h"


/**
 * Access the x coordinate of one point
 * @param  ponto [point to see the x coordinte]
 * @return       [x coordinate from point]
 */
int get_X_From_Point(point * ponto)
{
    return ponto->x;
}


/**
 * Access the y coordinate of one point
 * @param  ponto [point to see the y coordinate]
 * @return       [y coordinate from point]
 */
int get_Y_From_Point(point * ponto)
{
    return ponto->y;
}

size_t getSizeOfPoint()
{
    return sizeof(point );
}

size_t getSizeOfPointAst()
{
    return sizeof(point *);
}


/**
 * Given 2 points checks if are the same point
 * @param  ponto1 [point 1]
 * @param  ponto2 [point 2]
 * @return        [true in case of being the same point]
 */
bool SamePoint(point * ponto1,  point * ponto2)
{
    if( get_X_From_Point(ponto1) == get_X_From_Point(ponto2) && get_Y_From_Point(ponto1) == get_Y_From_Point(ponto2))
        return true;
    else
        return false;
}

/**
 * Given 2 points cheks if it is a horse jump
 * @param  ponto1 [description]
 * @param  ponto2 [description]
 * @return        [description]
 */
bool CheckHorseJump(point * ponto1,  point * ponto2)
{
    if (SamePoint(ponto1, ponto2))
        return false;

    // the point2 is 2 cells above the point1 or the point2 it 2 cells under point1
    if((get_Y_From_Point(ponto1) == (get_Y_From_Point(ponto2) + 2)) || (get_Y_From_Point(ponto1) == (get_Y_From_Point(ponto2) - 2)) )
    {
        // now the point2 only can be 1 cell to the left or 1 cell to the right
        if((get_X_From_Point(ponto1) == (get_X_From_Point(ponto2) + 1)) || (get_X_From_Point(ponto1) == (get_X_From_Point(ponto2) - 1)) )
            return true;
    }
    // the point2 is 2 cells on the left of point1 or the point2 it 2 cells on the right of point1
    else if((get_X_From_Point(ponto1) == (get_X_From_Point(ponto2) + 2)) || (get_X_From_Point(ponto1) == (get_X_From_Point(ponto2) - 2)) )
    {
        // now the point2 only can be 1 cell under or 1 cell above the point1
        if((get_Y_From_Point(ponto1) == (get_Y_From_Point(ponto2) + 1)) || (get_Y_From_Point(ponto1) == (get_Y_From_Point(ponto2) - 1)) )
            return true;
    }

    return false;
}

point * SetPoint(point * ponto, int x, int y)
{
    ponto->x = x;
    ponto->y = y;
    return ponto;
}
