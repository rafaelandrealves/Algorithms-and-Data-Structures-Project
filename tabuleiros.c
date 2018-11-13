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
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"

#define PrintStructs 0


/**
 * Reads and saves the information of one problem in the input file
 * @param  fp          [file pointer to the reading file]
 * @param  end_of_file [variable that checks if reached the end of file]
 * @return             [returns the main struct of the program with the new data (or empty in case of EOF)]
 */
UNICODE * Read_File(FILE * fp, bool *end_of_file)
{
    UNICODE * new = (UNICODE *) Checked_Malloc(sizeof(UNICODE));



    if(fscanf(fp, "%d %d %c %d", &new->tabu.size_y, &new->tabu.size_x, &new->modo_jogo, &new->passadeira_vermelha.num_pontos) != 4)
    {
        *end_of_file = true;
        return new;
    }

    new->tabu.tab = (int **) Checked_Malloc(new->tabu.size_y * sizeof(int*));
    for(int i = 0; i < new->tabu.size_y; i++)
        new->tabu.tab[i] = (int *) Checked_Malloc(new->tabu.size_x * sizeof(int));

    new->passadeira_vermelha.points = (point *) Checked_Malloc( new->passadeira_vermelha.num_pontos * sizeof(point));


    for(int i = 0; i < new->passadeira_vermelha.num_pontos; i++)
        fscanf(fp, "%d %d", &new->passadeira_vermelha.points[i].y, &new->passadeira_vermelha.points[i].x);


    for(int yy = 0; yy < new->tabu.size_y; yy++)
    {
       for(int xx = 0; xx < new->tabu.size_x; xx++)
           fscanf(fp, "%d ", &new->tabu.tab[yy][xx]);
    }

    #if PrintStructs == 1
        PrintMainStruct(new);
    #endif

    return new;
}



/**
 * Checks if one point is inside the table
 * @param  table [city map]
 * @param  ponto [point to check if is inside the table]
 * @return       [returns true is is inside the table]
 */
bool check_Point_Inside_Table(tabuleiro table, point ponto)
{
    int x = get_X_From_Point(ponto);
    int y = get_Y_From_Point(ponto);

    if((x < table.size_x) && (x >= 0) && (y < table.size_y) && (y >= 0))
        return true;

    return false;

}

/**
 * Returns the cost of one given point
 * @param  table [table matrix]
 * @param  ponto [point to get the cost]
 * @return       [cost of that point]
 */
int GetPointCost(tabuleiro table, point ponto)
{
    return (table.tab[get_Y_From_Point(ponto)][get_X_From_Point(ponto)]);
}
