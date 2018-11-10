


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"


/**
 * Access the x coordinate of one point
 * @param  ponto [point to see the x coordinate]
 * @return       [x coordinate from point]
 */
int get_X_From_Point(point ponto)
{
    return ponto.x;

}


/**
 * Access the y coordinate of one point
 * @param  ponto [point to see the y coordinate]
 * @return       [y coordinate from point]
 */
int get_Y_From_Point(point ponto)
{
    return ponto.y;
}
