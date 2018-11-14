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

struct tabuleiro_t
{
    int size_x; // sizes of the table
    int size_y;
    short ** tab; // table matrix
};


int getXSize(tabuleiro table)
{
    return table.size_x;
}

int getYSize(tabuleiro table)
{
    return table.size_y;
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
int GetPointCostFromPoint(tabuleiro table, point ponto)
{
    return (int)(table.tab[get_Y_From_Point(ponto)][get_X_From_Point(ponto)]);
}

int GetPointCostFromCoord(tabuleiro table, int yy, int xx)
{
    return (int)(table.tab[yy][xx]);
}

/**
 * Writes the file with the failure
 * @param cavaleiro [main struct]
 * @param NULL      [file pointer]
 */
void WriteFileWithFailure(Problema * turist, FILE * fp_out)
{
    fprintf(fp_out, "%d %d %c %d -1 0\n\n", turist->tabu.size_y, turist->tabu.size_x, turist->modo_jogo, turist->passadeira_vermelha.num_pontos);
}

/**
 * Wirtes the file with success
 * @param turist [main struct]
 * @param fp_out [file pointer]
 */
void WriteFileWithSuccess(Problema * turist, FILE * fp_out)
{
    fprintf(fp_out, "%d %d %c %d 1 %d\n\n", turist->tabu.size_y, turist->tabu.size_x, turist->modo_jogo, turist->passadeira_vermelha.num_pontos, turist->passadeira_vermelha.custo_total);
}

tabuleiro * Set_Lenght_Width(tabuleiro * table, int sizey, int sizex)
{
    table->size_x = sizex;
    table->size_y = sizey;
    new->tab = (short **) Checked_Malloc(sizey * sizeof(short*));
    for(int i = 0; i < sizey; i++)
        new->tab[i] = (short *) Checked_Malloc(sizex * sizeof(short));

    return table;
}

void SetMatrixElement(tabuleiro * table, short cost, int yy, int xx)
{
    table->tab[yy][xx] = cost;
}
