


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"

struct point_t
{
    int x;
    int y;
};



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
void movimentos_num_ponto(Problema *new, int xmax, int ymax, int x, int y, char condicao, int *soma_min)
{
    int soma2=0, soma1=0;

    if(condicao == 'y')
    {
        if(x < xmax && (y+1) < ymax && x >= 0)
        {
            soma1 = new->tabu.tab[y+1][x];
        }
        if(x < xmax && x >= 0 && (y-1) >= 0)
        {
            soma2 = new->tabu.tab[y-1][x];
        }
        if( soma1 <= *soma_min && soma1 != 0){
            *soma_min=soma1;
        }
        if( soma2 <= *soma_min && soma2 != 0){
            *soma_min=soma2;
        }
    }
    else
    {
        if((x+1) < xmax && y < ymax && y >= 0)
        {
            soma1 = new->tabu.tab[y][x + 1];

        }
        if( y < ymax && (x-1) >= 0 && y >= 0)
        {
            soma2 = new->tabu.tab[y][x - 1];

        }
        if( soma1 <= *soma_min && soma1 != 0){
            *soma_min=soma1;
        }
        if( soma2 <= *soma_min && soma2 != 0){
            *soma_min=soma2;
        }
    }
}

/**
 * Access the x coordinate of one point
 * @param  ponto [point to see the x coordinte]
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


/**
 * Given 2 points checks if are the same point
 * @param  ponto1 [point 1]
 * @param  ponto2 [point 2]
 * @return        [true in case of being the same point]
 */
bool SamePoint(point ponto1,  point ponto2)
{
    if(get_X_From_Point(ponto1) == get_X_From_Point(ponto2) && get_Y_From_Point(ponto1) == get_Y_From_Point(ponto2))
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
bool CheckHorseJump(point ponto1,  point ponto2)
{
    if (SamePoint(ponto1,  ponto2))
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

point * SetPoint(point * ponto, short x, short y)
{
    ponto->x = x;
    ponto->y = y;
    return ponto;
}
